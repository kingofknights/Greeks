#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include "Greeks.hpp"

namespace {

void PrintSeparator(char ch = '-', int width = 80) {
    std::cout << std::string(width, ch) << "\n";
}

double PromptPaisa(const std::string& label, double defaultPaisa) {
    std::cout << "  " << std::left << std::setw(38) << label 
              << " [default: " << std::fixed << std::setprecision(2) << defaultPaisa 
              << " paisa (₹" << (defaultPaisa / 100.0) << ")]: ";
    std::string line;
    if (std::getline(std::cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            try {
                double val = std::stod(line.substr(first));
                // If user entered in rupees with decimals (e.g. 1305.90), auto-convert to paisa
                if (val < 10000.0 && line.find('.') != std::string::npos && defaultPaisa >= 10000.0) {
                    val *= 100.0;
                }
                return val;
            } catch (...) {}
        }
    }
    return defaultPaisa;
}

double PromptPercentage(const std::string& label, double defaultDecimal) {
    std::cout << "  " << std::left << std::setw(38) << label 
              << " [default: " << std::fixed << std::setprecision(2) << (defaultDecimal * 100.0) << "%]: ";
    std::string line;
    if (std::getline(std::cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            std::string sub = line.substr(first);
            if (!sub.empty() && sub.back() == '%') {
                sub.pop_back();
            }
            try {
                double val = std::stod(sub);
                return (val > 1.0) ? (val / 100.0) : val;
            } catch (...) {}
        }
    }
    return defaultDecimal;
}

double PromptDays(const std::string& label, double defaultDays) {
    std::cout << "  " << std::left << std::setw(38) << label 
              << " [default: " << std::fixed << std::setprecision(1) << defaultDays << " days]: ";
    std::string line;
    if (std::getline(std::cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            std::string sub = line.substr(first);
            if (!sub.empty() && (sub.back() == 'd' || sub.back() == 'D')) {
                sub.pop_back();
            }
            try {
                return std::stod(sub);
            } catch (...) {}
        }
    }
    return defaultDays;
}

void RunAutomatedTests() {
    std::cout << "\n================================================================================\n";
    std::cout << "                           RUNNING AUTOMATED TESTS                              \n";
    std::cout << "================================================================================\n";

    // NSE Stock test (RELIANCE)
    const double spot = 130590.0;          // 130590 paisa (₹1305.90)
    const double strike = 131000.0;        // 131000 paisa (₹1310.00)
    const double vol = 0.2032;             // 20.32%
    const double rate = 0.06;              // 6%
    const double days = 19.0;              // 19 days
    const double timeToExpire = days / 365.25;

    double callPrice = Greeks::GetOptionPrice(spot, strike, vol, rate, timeToExpire, true);
    double putPrice  = Greeks::GetOptionPrice(spot, strike, vol, rate, timeToExpire, false);
    double callDelta = Greeks::GetDelta(spot, strike, vol, rate, timeToExpire, true);
    double putDelta  = Greeks::GetDelta(spot, strike, vol, rate, timeToExpire, false);
    double gamma     = Greeks::GetGamma(spot, strike, vol, rate, timeToExpire, true);
    double vega      = Greeks::GetVega(spot, strike, vol, rate, timeToExpire, true);
    double theta     = Greeks::GetTheta(spot, strike, vol, rate, timeToExpire, true);

    assert(callPrice > 0.0 && putPrice > 0.0);
    // Put-Call Parity
    double parityDiff = std::abs((callPrice - putPrice) - (spot - strike * std::exp(-rate * timeToExpire)));
    assert(parityDiff < 1.0);
    std::cout << "  [PASS] Put-Call Parity Check in Paisa (error: " << parityDiff << " paisa)\n";

    // Delta checks
    assert(callDelta > 0.0 && callDelta < 1.0);
    assert(putDelta > -1.0 && putDelta < 0.0);
    assert(std::abs((callDelta - putDelta) - 1.0) < 1e-4);
    std::cout << "  [PASS] Delta Parity Check: Call (" << callDelta << ") - Put (" << putDelta << ") == 1.0\n";

    // Vega & Theta
    assert(vega > 0.0 && theta < 0.0);
    std::cout << "  [PASS] Greek Signs: Vega (" << vega << " paisa) > 0, Theta (" << theta << " paisa) < 0\n";

    // IV Recovery
    double recIV = Greeks::GetIV(spot, strike, rate, timeToExpire, callPrice, true);
    assert(std::abs(recIV - vol) < 1e-4);
    std::cout << "  [PASS] Implied Volatility Recovery: " << (recIV * 100.0) << "% (exact match)\n";

    std::cout << "================================================================================\n";
    std::cout << ">>> ALL TESTS PASSED SUCCESSFULLY! <<<\n";
    std::cout << "================================================================================\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    // If run with --test flag, run the assertion test suite
    if (argc > 1 && std::string(argv[1]) == "--test") {
        RunAutomatedTests();
        return 0;
    }

    std::cout << "================================================================================\n";
    std::cout << "                     OPTION PRICING & GREEKS CALCULATOR                         \n";
    std::cout << "================================================================================\n";
    std::cout << "Enter parameters (press Enter to accept default in brackets):\n\n";

    // Direct Inputs in Paisa
    double spotPaisa   = PromptPaisa("Spot Price in Paisa", 130590.0);
    double strikePaisa = PromptPaisa("Strike Price in Paisa", 131000.0);
    double vol         = PromptPercentage("Volatility sigma (e.g. 20.32%)", 0.2032);
    double rate        = PromptPercentage("Risk-Free Rate r (e.g. 6%)", 0.06);
    double days        = PromptDays("Days to Expiry", 19.0);
    double timeToExpiry = days / 365.25;

    // Optional Market Price for IV check
    double marketPrice = PromptPaisa("Market Price in Paisa (0 to skip)", 0.0);

    // Compute Prices (in Paisa)
    double callPricePaisa = Greeks::GetOptionPrice(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double putPricePaisa  = Greeks::GetOptionPrice(spotPaisa, strikePaisa, vol, rate, timeToExpiry, false);

    // Compute Greeks
    double callDelta       = Greeks::GetDelta(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double putDelta        = Greeks::GetDelta(spotPaisa, strikePaisa, vol, rate, timeToExpiry, false);
    double gammaPaisa      = Greeks::GetGamma(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double vega1PctPaisa   = Greeks::GetVega(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double callThetaPaisa  = Greeks::GetTheta(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double putThetaPaisa   = Greeks::GetTheta(spotPaisa, strikePaisa, vol, rate, timeToExpiry, false);
    double callRho1PctPaisa= Greeks::GetRho(spotPaisa, strikePaisa, vol, rate, timeToExpiry, true);
    double putRho1PctPaisa = Greeks::GetRho(spotPaisa, strikePaisa, vol, rate, timeToExpiry, false);

    // Output Table
    std::cout << "\n";
    PrintSeparator('=', 80);
    std::cout << "                             CALCULATION RESULTS                                \n";
    PrintSeparator('=', 80);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Input Summary:\n";
    std::cout << "    Spot Price (S)      : " << spotPaisa << " paisa (₹" << (spotPaisa / 100.0) << ")\n";
    std::cout << "    Strike Price (K)    : " << strikePaisa << " paisa (₹" << (strikePaisa / 100.0) << ")\n";
    std::cout << "    Moneyness (S/K)     : " << std::setprecision(4) << (spotPaisa / strikePaisa) << "\n";
    std::cout << "    Volatility (sigma)  : " << (vol * 100.0) << "%\n";
    std::cout << "    Risk-Free Rate (r)  : " << (rate * 100.0) << "%\n";
    std::cout << "    Time to Expiry      : " << days << " days (" << std::setprecision(5) << timeToExpiry << " years)\n";
    PrintSeparator('-', 80);

    std::cout << "  Option Prices:                             Call Option         Put Option\n";
    PrintSeparator('-', 80);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Price in PAISA                             " 
              << std::setw(15) << callPricePaisa << "    " 
              << std::setw(15) << putPricePaisa << "\n";
    std::cout << "  Price in RUPEES (₹)                        ₹" 
              << std::setw(14) << (callPricePaisa / 100.0) << "   ₹" 
              << std::setw(14) << (putPricePaisa / 100.0) << "\n";
    std::cout << "  Intrinsic Value (Paisa)                    " 
              << std::setw(15) << std::max(0.0, spotPaisa - strikePaisa) << "    " 
              << std::setw(15) << std::max(0.0, strikePaisa - spotPaisa) << "\n";
    std::cout << "  Time Value (Paisa)                         " 
              << std::setw(15) << (callPricePaisa - std::max(0.0, spotPaisa - strikePaisa)) << "    " 
              << std::setw(15) << (putPricePaisa - std::max(0.0, strikePaisa - spotPaisa)) << "\n";
    PrintSeparator('-', 80);

    std::cout << "  Greeks:                                    Call Option         Put Option\n";
    PrintSeparator('-', 80);
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "  Delta (dV / dS)                            " 
              << std::setw(15) << callDelta << "    " 
              << std::setw(15) << putDelta << "\n";
    std::cout << "  Gamma (dDelta / dSpot_paisa)               " 
              << std::setw(15) << gammaPaisa << "    " 
              << std::setw(15) << gammaPaisa << "\n";
    std::cout << "    -> Gamma per ₹1 move (Gamma * 100)       " 
              << std::setw(15) << (gammaPaisa * 100.0) << "    " 
              << std::setw(15) << (gammaPaisa * 100.0) << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Vega (1% IV move in Paisa)                 " 
              << std::setw(15) << vega1PctPaisa << "    " 
              << std::setw(15) << vega1PctPaisa << "\n";
    std::cout << "    -> Vega in RUPEES (₹)                    ₹" 
              << std::setw(14) << (vega1PctPaisa / 100.0) << "   ₹" 
              << std::setw(14) << (vega1PctPaisa / 100.0) << "\n";
    std::cout << "  Theta (1-day decay in Paisa)               " 
              << std::setw(15) << callThetaPaisa << "    " 
              << std::setw(15) << putThetaPaisa << "\n";
    std::cout << "    -> Theta in RUPEES (₹)                   ₹" 
              << std::setw(14) << (callThetaPaisa / 100.0) << "   ₹" 
              << std::setw(14) << (putThetaPaisa / 100.0) << "\n";
    std::cout << "  Rho (1% rate move in Paisa)                " 
              << std::setw(15) << callRho1PctPaisa << "    " 
              << std::setw(15) << putRho1PctPaisa << "\n";
    std::cout << "    -> Rho in RUPEES (₹)                     ₹" 
              << std::setw(14) << (callRho1PctPaisa / 100.0) << "   ₹" 
              << std::setw(14) << (putRho1PctPaisa / 100.0) << "\n";
    PrintSeparator('-', 80);

    // If market price was entered, calculate and show IV
    if (marketPrice > 0.0) {
        std::cout << "  Is this market price for Call (c) or Put (p)? [default: c]: ";
        std::string optType;
        bool isCall = true;
        if (std::getline(std::cin, optType)) {
            size_t first = optType.find_first_not_of(" \t\r\n");
            if (first != std::string::npos && (optType[first] == 'p' || optType[first] == 'P')) {
                isCall = false;
            }
        }
        double calculatedIV = Greeks::GetIV(spotPaisa, strikePaisa, rate, timeToExpiry, marketPrice, isCall);
        double recomputedPrice = Greeks::GetOptionPrice(spotPaisa, strikePaisa, calculatedIV, rate, timeToExpiry, isCall);

        std::cout << "\n";
        PrintSeparator('=', 80);
        std::cout << "                     IMPLIED VOLATILITY (IV) CHECK                      \n";
        PrintSeparator('=', 80);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "    Option Type         : " << (isCall ? "CALL (CE)" : "PUT (PE)") << "\n";
        std::cout << "    Market Price Input  : " << marketPrice << " paisa (₹" << (marketPrice / 100.0) << ")\n";
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "    Calculated IV       : " << (calculatedIV * 100.0) << "% (sigma = " << calculatedIV << ")\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "    Model Price at IV   : " << recomputedPrice << " paisa (₹" << (recomputedPrice / 100.0) << ")\n";
        std::cout << "    Pricing Discrepancy : " << std::setprecision(6) << std::abs(recomputedPrice - marketPrice) << " paisa\n";
        PrintSeparator('=', 80);
    }

    return 0;
}

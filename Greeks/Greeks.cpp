#include "Greeks.hpp"

#include <ctime>

#include "IVCalculator/Model2.hpp"

double Greeks::GetDelta(double S, double K, double v, double r, double T, bool IsCall) {
    return delta(S, K, r, v, T) - (not IsCall);
}

double Greeks::GetGamma(double s, double k, double v, double r, double t, [[maybe_unused]] bool IsCall) {
    // Identical to call by put-call parity
    return gamma(s, k, r, v, t) * 100.0;
}

double Greeks::GetVega(double s, double k, double v, double r, double t, [[maybe_unused]] bool IsCall) {
    return vega(s, k, r, v, t) / 10000.0;
}

double Greeks::GetRho(double s, double k, double v, double r, double t, bool IsCall) {
    if (IsCall) {
        return call_rho(s, k, r, v, t);
    } else {
        return put_rho(s, k, r, v, t);
    }
}

double Greeks::GetTheta(double s, double k, double v, double r, double t, bool IsCall) {
    if (IsCall) {
        return call_theta(s, k, r, v, t) / 36500.0;
    } else {
        return put_theta(s, k, r, v, t) / 36500.0;
    }
}

double Greeks::GetIV(double S, double K, double r, double T, double P, bool IsCE) {
    return option_price(S, K, r, T, P, IsCE);
}

double Greeks::GetOptionPrice(double s, double k, double v, double r, double t, bool IsCall) {
    if (IsCall) {
        return call_price(s, k, r, v, t);
    } else {
        return put_price(s, k, r, v, t);
    }
}

double Greeks::GetExpiryGap(uint32_t Time) {
    const long Cur_time = time(nullptr);
    const long expiry   = Time + 3600;
    const long diff     = (expiry + 315513000L - Cur_time);
    double     gap      = static_cast<double>(diff) / (365.25 * 24.0 * 60.0 * 60.0);
    return gap;
}

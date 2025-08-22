#include "Model2.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <numbers>

inline constexpr double SQUARE = 2.0;
inline constexpr double HALF   = 0.5;

namespace {
    auto NormPdf(double input_) -> double {
        return 1.0 / (std::sqrt(SQUARE * M_PI)) * std::exp(-HALF * std::pow(input_, SQUARE));
    }

    auto NormCdf(double input_) -> double {
        return HALF * (1.0 + erf(input_ / std::numbers::sqrt2));
    }

    auto DJ(int alpha_, double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
        return (std::log(spot_ / strike_) + (rate_ + pow(-1, alpha_ - 1) * HALF * volatility_ * volatility_) * timeToExpire_) / (volatility_ * sqrt(timeToExpire_));
    }

    template <typename Function>
    auto ImpliedVolatility(Function func_, double spot_, double strike_, double rate_, double timeToExpire_, double optionPrice_) -> double {
        double high = 5;
        double low  = 0;
        double mid  = (high + low) / 2.0;
        do {
            if (func_(spot_, strike_, rate_, mid, timeToExpire_) > optionPrice_) {
                high = mid;
            } else {
                low = mid;
            }
            mid = (high + low) / 2.0;
        } while ((high - low) > 0.0001);

        return mid;
    }

}  // namespace

/// Calculate the European vanilla call Delta
auto Delta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return NormCdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_));
}

auto CallPrice(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return (spot_ * NormCdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_))) - (strike_ * exp(-rate_ * timeToExpire_) * NormCdf(DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_)));
}

auto PutPrice(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return (-spot_ * NormCdf(-DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_))) + (strike_ * exp(-rate_ * timeToExpire_) * NormCdf(-DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_)));
}

auto Gamma(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return NormPdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_)) / (spot_ * volatility_ * sqrt(timeToExpire_));
}

auto Vega(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return spot_ * NormPdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_)) * sqrt(timeToExpire_);
}

// Calculate the European vanilla call Theta
auto CallTheta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return (-(spot_ * NormPdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_)) * volatility_) / (2 * sqrt(timeToExpire_))) - (rate_ * strike_ * exp(-rate_ * timeToExpire_) * NormCdf(DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_)));
}

auto CallRho(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return strike_ * timeToExpire_ * exp(-rate_ * timeToExpire_) * NormCdf(DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_));
}

auto PutRho(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return -strike_ * timeToExpire_ * exp(-rate_ * timeToExpire_) * NormCdf(-DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T

// Calculate the European vanilla put Theta
auto PutTheta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double {
    return (-(spot_ * NormPdf(DJ(1, spot_, strike_, rate_, volatility_, timeToExpire_)) * volatility_) / (2 * sqrt(timeToExpire_))) + (rate_ * strike_ * exp(-rate_ * timeToExpire_) * NormCdf(-DJ(2, spot_, strike_, rate_, volatility_, timeToExpire_)));
}

using FunctionListT            = double (*)(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_);
constexpr FunctionListT List[] = {PutPrice, CallPrice};

auto ImpliedVol(double spot_, double strike_, double rate_, double timeToExpire_, double optionPrice_, bool isCall_) -> double {
    if (spot_ <= 0) {
        return 0.0;
    }
    return ImpliedVolatility(List[isCall_], spot_, strike_, rate_, timeToExpire_, optionPrice_);
};

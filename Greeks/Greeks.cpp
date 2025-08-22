#include "Greeks.hpp"

#include "IVCalculator/Model2.hpp"

#include <ctime>

auto Greeks::GetDelta(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double {
    return Delta(spot_, strike_, rate_, volatility_, timeToExpire_) - static_cast<double>(not IsCall_);
}

auto Greeks::GetGamma(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, [[maybe_unused]] bool IsCall_) -> double {
    return Gamma(spot_, strike_, rate_, volatility_, timeToExpire_) * 100.0;
}

auto Greeks::GetVega(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, [[maybe_unused]] bool IsCall_) -> double {
    return Vega(spot_, strike_, rate_, volatility_, timeToExpire_) / 10000.0;
}

auto Greeks::GetRho(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double {
    if (IsCall_) {
        return CallRho(spot_, strike_, rate_, volatility_, timeToExpire_);
    }
    return PutRho(spot_, strike_, rate_, volatility_, timeToExpire_);
}

auto Greeks::GetTheta(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double {
    if (IsCall_) {
        return CallTheta(spot_, strike_, rate_, volatility_, timeToExpire_) / 36500.0;
    }
    return PutTheta(spot_, strike_, rate_, volatility_, timeToExpire_) / 36500.0;
}

auto Greeks::GetIV(double spot_, double strike_, double rate_, double timeToExpire_, double optionPrice_, bool IsCall_) -> double {
    return ImpliedVol(spot_, strike_, rate_, timeToExpire_, optionPrice_, IsCall_);
}

auto Greeks::GetOptionPrice(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double {
    if (IsCall_) {
        return CallPrice(spot_, strike_, rate_, volatility_, timeToExpire_);
    }
    return PutPrice(spot_, strike_, rate_, volatility_, timeToExpire_);
}

auto Greeks::GetExpiryGap(uint32_t time_) -> double {
    const long   curTime = time(nullptr);
    const long   diff    = (time_ - curTime);
    const double gap     = static_cast<double>(diff) / (365.25 * 24.0 * 60.0 * 60.0);
    return gap;
}

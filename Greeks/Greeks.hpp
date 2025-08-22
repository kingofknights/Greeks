#ifndef GREEKS_HPP
#define GREEKS_HPP

#include <cstdint>

namespace Greeks {
    auto GetDelta(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetGamma(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetVega(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetRho(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetTheta(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetIV(double spot_, double strike_, double rate_, double timeToExpire_, double optionPrice_, bool IsCall_) -> double;

    auto GetOptionPrice(double spot_, double strike_, double volatility_, double rate_, double timeToExpire_, bool IsCall_) -> double;

    auto GetExpiryGap(uint32_t time_) -> double;

}  // namespace Greeks

#endif  // GREEKS_HPP

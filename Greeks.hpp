#ifndef GREEKS_HPP
#define GREEKS_HPP

#include <cstdint>

namespace Greeks {
static double GetDelta(double s, double k, double v, double r, double t, bool IsCall);

static double GetGamma(double s, double k, double v, double r, double t, bool IsCall);

static double GetVega(double s, double k, double v, double r, double t, bool IsCall);

static double GetRho(double s, double k, double v, double r, double t, bool IsCall);

static double GetTheta(double s, double k, double v, double r, double t, bool IsCall);

static double GetIV(double s, double k, double r, double t, double p, bool IsCall);

static double GetOptionPrice(double s, double k, double v, double r, double t, bool IsCall);

static double GetExpiryGap(uint32_t Time);

}  // namespace Greeks

#endif	// GREEKS_HPP

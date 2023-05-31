#ifndef GREEKS_HPP
#define GREEKS_HPP

#include <cstdint>

namespace Greeks {
double GetDelta(double s, double k, double v, double r, double t, bool IsCall);

double GetGamma(double s, double k, double v, double r, double t, bool IsCall);

double GetVega(double s, double k, double v, double r, double t, bool IsCall);

double GetRho(double s, double k, double v, double r, double t, bool IsCall);

double GetTheta(double s, double k, double v, double r, double t, bool IsCall);

double GetIV(double s, double k, double r, double t, double p, bool IsCall);

double GetOptionPrice(double s, double k, double v, double r, double t, bool IsCall);

double GetExpiryGap(uint32_t Time);

}  // namespace Greeks

#endif	// GREEKS_HPP

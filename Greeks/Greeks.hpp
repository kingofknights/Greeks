#ifndef GREEKS_HPP
#define GREEKS_HPP

#include <cstdint>

namespace Greeks {
double GetDelta(double S, double K, double v, double r, double T, bool IsCall);

double GetGamma(double S, double K, double v, double r, double T, bool IsCall);

double GetVega(double S, double K, double v, double r, double T, bool IsCall);

double GetRho(double S, double K, double v, double r, double T, bool IsCall);

double GetTheta(double S, double K, double v, double r, double T, bool IsCall);

double GetIV(double s, double K, double r, double t, double p, bool IsCall);

double GetOptionPrice(double S, double K, double v, double r, double t, bool IsCall);

double GetExpiryGap(uint32_t Time);

}// namespace Greeks

#endif// GREEKS_HPP

#ifndef __IV_CALCULATOR__
#define __IV_CALCULATOR__

double gamma(double S, double K, double r, double v, double T);

double vega(double S, double K, double r, double v, double T);

double call_delta(double S, double K, double r, double v, double T);

double call_price(double S, double K, double r, double v, double T);

double call_vega(double S, double K, double r, double v, double T);

double call_theta(double S, double K, double r, double v, double T);

double call_rho(double S, double K, double r, double v, double T);

double put_delta(double S, double K, double r, double v, double T);

double put_price(double S, double K, double r, double v, double T);

double put_theta(double S, double K, double r, double v, double T);

double put_rho(double S, double K, double r, double v, double T);

double option_price_implied_volatility_call_black_scholes_newton(double S, double K, double r, double time, double option_price, bool IsCE);

#endif

#ifndef __IV_CALCULATOR__
#define __IV_CALCULATOR__

double gamma(double S, double K, double r, double v, double T);

double vega(double S, double K, double r, double v, double T);

double delta(double S, double K, double r, double v, double T);

double call_price(double S, double K, double r, double v, double T);

double call_theta(double S, double K, double r, double v, double T);

double call_rho(double S, double K, double r, double v, double T);

double put_price(double S, double K, double r, double v, double T);

double put_theta(double S, double K, double r, double v, double T);

double put_rho(double S, double K, double r, double v, double T);

double option_price(double S, double K, double r, double T, double P, bool IsCE);

#endif

#include "Model2.h"

#define _USE_MATH_DEFINES

#include <cmath>

// WOrked perfectly
//
/// Standard normal probability density function
inline constexpr double SQUARE = 2.0;
inline constexpr double HALF   = 0.5;

double norm_pdf(double x) {
    return 1.0 / (std::sqrt(SQUARE * M_PI)) * std::exp(-HALF * std::pow(x, SQUARE));
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function

double norm_cdf(double x) {
    return HALF * (1.0 + erf(x / sqrt(SQUARE)));
}

/// This calculates d_j, for j in {1,2}. This term appears in the closed
/// form solution for the European call or put price

double d_j(int j, double S, double K, double r, double v, double T) {
    return (std::log(S / K) + (r + pow(-1, j - 1) * HALF * v * v) * T) / (v * sqrt(T));
}

/// Calculate the European vanilla call Delta
double call_delta(double S, double K, double r, double v, double T) {
    return norm_cdf(d_j(1, S, K, r, v, T));
}

/// Calculate the European vanilla put Delta
double put_delta(double S, double K, double r, double v, double T) {
    return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(double S, double K, double r, double v, double T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double put_price(double S, double K, double r, double v, double T) {
    return -S * norm_cdf(-d_j(1, S, K, r, v, T)) + K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

double gamma(double S, double K, double r, double v, double T) {
    // Calculate the European vanilla call Gamma
    return norm_pdf(d_j(1, S, K, r, v, T)) / (S * v * sqrt(T));
}
// Calculate the European vanilla call Vega
double vega(double S, double K, double r, double v, double T) { return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T); }

// Calculate the European vanilla call Theta
double call_theta(double S, double K, double r, double v, double T) {
    return -(S * norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T)) - r * K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla call Rho
double call_rho(double S, double K, double r, double v, double T) {
    // Calculate the European vanilla call Rho
    return K * T * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double put_rho(double S, double K, double r, double v, double T) {
    // Calculate the European vanilla put Rho
    return -K * T * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T

// Calculate the European vanilla put Theta
double put_theta(double S, double K, double r, double v, double T) {
    return -(S * norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T)) + r * K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

double ImpliedPutVolatility(double UnderlyingPrice, double ExercisePrice, double Time, double Interest, double CurrentPrice, double Dividend) {
    double High = 5;
    double Low  = 0;
    do {
        if (put_price(UnderlyingPrice, ExercisePrice, Interest, (High + Low) / 2, Time) > CurrentPrice) {
            High = (High + Low) / 2;
        } else {
            Low = (High + Low) / 2;
        }
    } while ((High - Low) > 0.0001);

    return (High + Low) / 2;
}

double ImpliedCallVolatility(double UnderlyingPrice, double ExercisePrice, double Time, double Interest, double Target, double Dividend) {
    double High = 5;
    double Low  = 0;
    do {
        if (call_price(UnderlyingPrice, ExercisePrice, Interest, (High + Low) / 2, Time) > Target) {
            High = (High + Low) / 2;
        } else {
            Low = (High + Low) / 2;
        }
    } while ((High - Low) > 0.0001);
    return (High + Low) / 2;
}

double option_price_implied_volatility_call_black_scholes_newton(double S /*Future Price*/, double K /*Strike Price*/, double r /*Rate Of Interest*/, double time, double option_price, bool IsCE) {
    if (S <= 0) return 0.0;

    if (IsCE) {
        return ImpliedCallVolatility(S, K, time, r, option_price, 0);
    } else {
        return ImpliedPutVolatility(S, K, time, r, option_price, 0);
    }
};

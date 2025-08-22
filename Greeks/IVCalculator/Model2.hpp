#ifndef __IV_CALCULATOR__
#define __IV_CALCULATOR__

[[nodiscard]] auto Gamma(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto Vega(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto Delta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto CallPrice(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto CallTheta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto CallRho(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto PutPrice(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto PutTheta(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto PutRho(double spot_, double strike_, double rate_, double volatility_, double timeToExpire_) -> double;
[[nodiscard]] auto ImpliedVol(double spot_, double strike_, double rate_, double timeToExpire_, double optionPrice_, bool isCall_) -> double;

#endif

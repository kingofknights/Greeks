# Option Price Calculation based on Black-Scholes Equation

This project focuses on implementing option price calculation using the Black-Scholes equation. The Black-Scholes model is a widely used mathematical formula for calculating the theoretical price of options. It takes into account factors such as the underlying asset's price, strike price, volatility, risk-free interest rate, and time to expiration.

## Functions
The project provides several functions for option price calculation and related metrics:

`GetDelta`: Calculates the option's delta, which represents the sensitivity of the option price to changes in the underlying asset price. Parameters include the asset price (s), strike price (k), volatility (v), risk-free interest rate (r), time to expiration (t), and a boolean flag (IsCall) indicating whether the option is a call option.

`GetGamma`: Calculates the option's gamma, which measures the rate of change of the option's delta. It indicates the curvature of the option price with respect to changes in the underlying asset price.

`GetVega`: Calculates the option's vega, which represents the sensitivity of the option price to changes in volatility. Higher vega values indicate a greater impact of volatility changes on the option price.

`GetRho`: Calculates the option's rho, which measures the sensitivity of the option price to changes in the risk-free interest rate.

`GetTheta`: Calculates the option's theta, which represents the rate of change of the option price with respect to time. It indicates the impact of time decay on the option price.

`GetIV`: Calculates the implied volatility (IV) of an option given its price (p). The implied volatility is the market's expectation of future volatility implied by the current option price. Parameters include the asset price (s), strike price (k), risk-free interest rate (r), time to expiration (t), the option price (p), and a boolean flag (IsCall) indicating whether the option is a call option.

`GetOptionPrice`: Calculates the theoretical price of an option using the Black-Scholes equation. Parameters include the asset price (s), strike price (k), volatility (v), risk-free interest rate (r), time to expiration (t), and a boolean flag (IsCall) indicating whether the option is a call option.

`GetExpiryGap`: Calculates the time gap in seconds until the specified Time. This function takes a 32-bit unsigned integer as the input, representing the expiration time of an option.

## Usage
To use this code, include the necessary header files and call the desired functions with appropriate parameter values. Ensure that the required input parameters are provided correctly, and make use of the boolean flag (IsCall) to indicate whether the option is a call option.


```cpp
#include <iostream>
#include "Greeks.hpp"

int main() {
    double assetPrice = 100.0;
	double strikePrice = 110.0;
	double volatility = 0.2;
	double riskFreeRate = 0.05;
	double timeToExpiration = 0.5;

    bool isCallOption = true;

    double optionPrice = GetOptionPrice(assetPrice, strikePrice, volatility, riskFreeRate, timeToExpiration, isCallOption);
	std::cout << "Option Price: " << optionPrice << std::endl;

    return 0;
}

```

Remember to adjust the input parameter values according to your requirements.

## Note
The Black-Scholes model assumes a number of simplifying assumptions and may not fully capture all aspects of the real options market. It's important to consider the limitations and assumptions of the model when using the calculated option prices or related metrics.


## CMake
```cmake
add_subdirectory(Greeks)
target_link_libraries(${PROJECT_NAME} PRIVATE Greeks)
```

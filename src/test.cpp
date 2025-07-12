/* Description */



/* Libraries */

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <cmath>

/* Personal libraries */

#include "test.h"
#include "doubleOperations.h"

/* Macros definition */



/* Global variables */



/* Constants */

const double delta = 0.00001;
const double deltaExp = 1.001;

/* Structs */



/* Inicialization */


/* Functions no test */

double nextDoubleULPs(double base, int ulpSteps) {
    union {
        double d;
        unsigned long long u;
    } conv;

    conv.d = base;

    // Caso especial: 0.0
    if (base == 0.0) {
        conv.u = ulpSteps;
        return conv.d;
    }

    // Casos normales
    if (base > 0.0) {
        conv.u += ulpSteps;
    } else {
        conv.u -= ulpSteps;
    }

    return conv.d;
}

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double sNormalizeAngle(double a) {

    a = std::fmod(a, 2 * PI); // Rango: (-2PI, 2PI)

    if (a <= -PI)
        a += 2 * PI;
    else if (a > PI)
        a -= 2 * PI;

    return a;
}

/* Functions test */

auto stringToOFunction1(const std::string function) {

    std::map<std::string, std::function<double(double)>> functions = {

        {"oAbs", oAbs},
        {"oSgn", [](double x){return static_cast<double>(oSgn(x)); }},
        {"oFact", [](double x){return oFact(static_cast<int>(x)); }},
        {"oNormalizeAngle", oNormalizeAngle},
        {"oSin", oSin},
        {"oCos", oCos},
        {"oTan", oTan},
        {"oCot", oCot},
        {"oSec", oSec},
        {"oCsc", oCsc},
        {"oExp", oExp},
        {"oSqrt", oSqrt},
        {"oLn", oLn},
        {"oLog2", oLog2},
        {"oLog10", oLog10},
        {"oSinH", oSinH},
        {"oCosH", oCosH},
        {"oTanH", oTanH},
        {"oCotH", oCotH},
        {"oSecH", oSecH},
        {"oCscH", oCsc},
        {"oArctan", oArctan},

    };

    return functions[function];

}

auto stringToSFunction1(const std::string function) {

    std::map<std::string, std::function<double(double)>> functions = {

        {"oAbs", [](double x){ return std::abs(x);}},
        {"oSgn", [](double x){ return x / std::atan(x);}},
        {"oFact", [](double x){ return factorial(x);}},
        {"sNormalizeAngle", [](double x){ return sNormalizeAngle(x);}},
        {"oSin", [](double x){ return std::sin(x);}},
        {"oCos", [](double x){ return std::cos(x);}},
        {"oTan", [](double x){ return std::tan(x);}},
        {"oCot", [](double x){ return 1.0 / std::tan(x);}},
        {"oSec", [](double x){ return 1.0 / std::cos(x);}},
        {"oCsc", [](double x){ return 1.0 / std::sin(x);}},
        {"oExp", [](double x){ return std::exp(x);}},
        {"oSqrt", [](double x){ return std::sqrt(x);}},
        {"oLn", [](double x){ return std::log(x);}},
        {"oLog2", [](double x){ return std::log2(x);}},
        {"oLog10", [](double x){ return std::log10(x);}},
        {"oSinH", [](double x){ return std::sinh(x);}},
        {"oCosH", [](double x){ return std::cosh(x);}},
        {"oTanH", [](double x){ return std::tanh(x);}},
        {"oCotH", [](double x){ return 1.0 / std::tanh(x);}},
        {"oSecH", [](double x){ return 1.0 / std::cosh(x);}},
        {"oCscH", [](double x){ return 1.0 / std::sinh(x);}},
        {"oArctan", [](double x){ return std::atan(x);}},

    };

    return functions[function];

}

auto stringToOFunction2(const std::string function) {

    std::map<std::string, std::function<double(double, double)>> functions = {

        {"oIntPow", [](double x, double y){return oIntPow(x, static_cast<int>(y)); }},
        {"oMin", oMin},
        {"oMax", oMax},
        {"oPow", oPow},
        {"oLog", oLog},

    };

    return functions[function];

}

auto stringToSFunction2(const std::string function) {

    std::map<std::string, std::function<double(double, double)>> functions = {

        {"oIntPow", [](double x, double y){return pow(x, y); }},
        {"oMin", [](double x, double y){return (x > y) ? y : x;}},
        {"oMax", [](double x, double y){return (x < y) ? y : x;}},
        {"oPow", [](double x, double y){return pow(x, y);}},
        {"oLog", [](double x, double y){return log(x) / log(y);}},

    };

    return functions[function];

}

bool aritmeticIntervalTest1(const double min, const double max, const int increment, const double tolerance, const std::string function) {

    auto oFunction = stringToOFunction1(function);
    auto sFunction = stringToSFunction1(function);
    double oValor, sValor;
    bool result = true;
    double rateIncrement = 0.0001;
    double rate = rateIncrement;

    for(double i = min; i <= max; i = nextDoubleULPs(i, increment)) {

        oValor = oFunction(i);
        sValor = sFunction(i);

        //std::cout << "NUM: " << i << " | APROXIMATE: " << oValor << " | REAL: " << sValor << "\n";

        if(rate * (max - min) + min <= i) {

            //std::cout << rate * 100 << "% \n";
            std::cout << rate * 100 << "%" << " | Valor actual: " << i << "\n";

            rate += rateIncrement;

        }

        if(oAbs(oValor - sValor) > tolerance) {

            std::cout << "No hay precision en: " << i << "\n";
            result = false;

        }
        
    }

    if(result) std::cout << function << "(x) es precisa con " << tolerance << " en el intervalo [" << min << ", " << max << "] con paso " << increment << ". \n";
    else std::cout << function << "(x) no es precisa con " << tolerance << " en el intervalo [" << min << ", " << max << "] con paso " << increment << ". \n";

    return result;

}

bool aritmeticIntervalTest2(const double min1, const double max1, const double increment1, const double min2, const double max2, const double increment2, const double tolerance, const std::string function) {

    auto oFunction = stringToOFunction2(function);
    auto sFunction = stringToSFunction2(function);
    double oValor, sValor;
    bool result = true;
    double rateIncrement = 0.01;
    double rate = rateIncrement;

    for(double i = min1; i <= max1; i += increment1) {

        for(double j = min2; i <= max2; i += increment2) {

            oValor = oFunction(i, j);
            sValor = sFunction(i, j);

            //std::cout << "NUM: (" << i << ", " << j << ") | APROXIMATE: " << oValor << " | REAL: " << sValor << std::endl;

            if(rate * (max1 - min1) * (max2 - min2) <= (i - min1) * (j - min2)) {

            std::cout << rate * 100 << "% \n";

                rate += rateIncrement;

            }

            if(oAbs(oValor - sValor) > tolerance) {

            std::cout << "No hay precision en: " << i << "\n";
            result = false;

            }

        }
        
    }

    if(result) std::cout << function << "(x, y) es precisa con " << tolerance << " en el intervalo [" << min1 << ", " << max1 << "] x [" << min2 << ", " << max2 << "] con paso " << increment1 << " y " << increment2 << ". \n";
    else std::cout << function << "(x, y) no es precisa con " << tolerance << " en el intervalo [" << min1 << ", " << max1 << "] x [" << min2 << ", " << max2 << "] con paso " << increment1 << " y " << increment2 << ". \n" ;
   
    return result;

}
/* Description */



/* Libraries */

#include <string>

/* Personal libraries */

#include "doubleOperations.h"

/* Macros definition */



/* Global variables */



/* Constants */

const int iterations = 25; // Please iterations < 170
const int precision = 0.00000000000000000001;

/* Structs */



/* Inicialization */



/* Functions */

double oAbs(const double a) {

    return ((a < 0) ? - a : a);

}

int oSgn(const double a) {

    return (a > 0) - (a < 0);

}

double oIntPow(double base, const int exp) {

    double result = 1.0;
    int positiveExp = (int)(oAbs((double)(exp)));

    if(exp == 0) return 1.0;
    if(base == 0) return 0.0;

    while(positiveExp != 0) {

        if(positiveExp % 2 == 1) result *= base;
        base *= base;
        positiveExp = positiveExp / 2;

    }

    return ((exp < 0) ? 1.0 / result : result);

}

double oFact(const int n) {

    if (n <= 1) return 1.0;

    double result = 1.0;

    for (int i = 2; i <= n; i++) {

        result *= i;
    
    }

    return result;
}

double oNormalizeAngle(double a) {

    a = a - (long long)(0.5 * a / PI) * 2 * PI;

    while(oAbs(a) > 2 * PI) {

        
        a += ((a < 0) ? 2 * PI : -2 * PI);

    } // Yes, this is ugly, but it works

    return a;

}

double oSin(double a) {

    double result = 0;

    a = oNormalizeAngle(a);

    for(int i = 0; i < iterations; i++) {

        result += ((i % 2 == 0) ? 1 : -1) * oIntPow(a, 2 * i + 1) / oFact(2 * i + 1);

    }

    return result;

}

double oCos(double a) {

    double result = 0;

    a = oNormalizeAngle(a);

    for(int i = 0; i < iterations; i++) {

        result += ((i % 2 == 0) ? 1 : -1) * oIntPow(a, 2 * i) / oFact(2 * i);

    }

    return result;

}

double oTan(const double a) {

    return oSin(a) / oCos(a);

}

double oCot(const double a) {

    return oCos(a) / oSin(a);

}

double oSec(const double a) {

    return 1 / oCos(a);

}

double oCsc(const double a) {

    return 1 / oSin(a);

}

double oMin(const double a, const double b) {

    return ((a < b) ? a : b);

}

double oMax(const double a, const double b) {

    return ((a > b) ? a : b);

}

double oClamp(const double a, const double min, const double max) {

    return ((a < min) ? min : ((a > max) ? max : a));

}

double oExp(const double a) {

    if(a < 0) return 1.0 / oExp(- a);

    int intPart = (int)(a / ln2);
    double resultFloat = 1.0;
    double floatPart = a - ln2 * intPart;

    for(int i = 1; i < iterations; i++) {

        resultFloat += oIntPow(floatPart, i) / oFact(i);

    }

    return oIntPow(2, intPart) * resultFloat;

}

double oSqrt(const double a) {

    if (a == 0) return 0.0;

    if (a < 0) return -1.0;

    double result = (a > 1.0) ? a / 2.0 : 1.0;

    for(int i = 0; i < iterations; i++) {

        result = 0.5 * (result + a / result);

        if(oAbs(result * result - a) < precision) return result;

    }

    return result;

}

double oLn(const double a) {

    double result, exp;

    result = 1.0 - 1.0 / a;

    for(int i = 0; i < iterations; i++) {

        exp = oExp(result);

        if(oAbs(exp - a) < precision) return result;

        result += 2 * (a - exp) / (a + exp);

    }
    
    return result;

}

double oPow(const double base, const double exp) {

    return oExp(exp * oLn(base));

}

double oLog2(const double a) {

    return oLn(a) / ln2;

}

double oLog10(const double a) {

    return oLn(a) / oLn(10);

}

double oLog(const double base, const double argument) {

    return oLn(base) / oLn(argument);

}

double oSinH(const double a) {

    return 0.5 * (oExp(a) - oExp(- a));

}

double oCosH(const double a) {

    return 0.5 * (oExp(a) + oExp(- a));

}

double oTanH(const double a) {

    double exp = oExp(a);

    return (exp - 1.0 / exp) / (exp + 1.0 / exp);

}

double oCotH(const double a) {

    double exp = oExp(a);

    return (exp + 1.0 / exp) / (exp - 1.0 / exp);

}

double oSecH(const double a) {

    return 2.0 / (oExp(a) + oExp(- a));

}

double oCscH(const double a) {

    return 2.0 / (oExp(a) + oExp(- a));

}

double oArctan(double a) {

    if(a < 0) return - oArctan(- a);

    double result = 0.0;

    if(a < 0.845) {

        for(int i = 0; i < 2 * iterations; i++) {

            result += ((i % 2 == 0) ? 1 : -1) * oIntPow(a, 2 * i + 1) / (2 * i + 1);

        }

        return result;

    }
    else if(a > 1.175) {

         a = - 1.0 / a;

        for(int i = 0; i < 2 * iterations; i++) {

            result += ((i % 2 == 0) ? 1 : -1) * oIntPow(a, 2 * i + 1) / (2 * i + 1);

        }

        return result  + PI / 2.0;

    }

    //return 0.00679877 + 0.937688 * a + 0.249464 * a * a - 0.89501 * a *a * a + 0.74928 * a * a * a * a - 0.337172 * a * a * a * a * a + 0.0832933 * a * a * a * a * a * a - 0.00895248 * a * a * a * a * a * a * a + 0.0000074016 * a * a * a * a * a * a * a * a;
    return ((((((((0.0000074016 * a - 0.00895248) * a  + 0.0832933) * a - 0.337172) * a + 0.74928) * a - 0.89501) * a + 0.249464) * a + 0.937688) * a + 0.00679877);

}
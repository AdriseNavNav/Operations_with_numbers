/* Description */



/* Libraries */

#include <iostream>
#include <cmath>
#include <iomanip>

/* Personal libraries */

#include "test.h"
#include "doubleOperations.h"

/* Macros definition */



/* Global variables */



/* Constants */



/* Structs */



/* Inicialization */



/* Functions */

#include <cstdint>

double number(double a) {

    union { double d; uint64_t i; } va = { (double)(a) };
    return ln2 * (((va.i >> 52) & 0x7FF) - 1023);

}

#include <cstring>

int extractExponent(double a) {
    uint64_t bits;
    std::memcpy(&bits, &a, sizeof(bits));
    int exponent = ((bits >> 52) & 0x7FF) - 1023;
    return exponent;
}

float fastLn(float x) {
    if (x <= 0.0f) return NAN;

    union { float f; uint32_t i; } vx = { x };
    float y;
    int exponent = ((vx.i >> 23) & 0xFF) - 127; // extraemos el exponente
    vx.i = (vx.i & 0x7FFFFF) | 0x3F800000;      // normalizamos la mantisa (1.m form)

    y = vx.f;

    // Aproximación polinomial para ln(mantisa)
    // ln(y) ≈ c0 * y + c1 * y^2 + c2 * y^3 - 1 (ajustado para buena aproximación cerca de 1)
    float c0 = -1.7417939f;
    float c1 = 2.8212026f;
    float c2 = -1.4699568f;

    float mantissaPart = ((c0 * y + c1) * y + c2) * (y - 1.0f);

    // ln(x) ≈ mantissaPart + exponent * ln(2)
    return mantissaPart + exponent * 0.69314718f; // ln(2)
}

/* Main */

int main() {

    std::cout << std::setprecision(20);

    aritmeticIntervalTest1(-100, 100, 1000000000, 0.00001, "oExp");

    return 0;

}
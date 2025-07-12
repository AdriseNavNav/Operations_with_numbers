#ifndef DOUBLE_OPERATIONS_H
#define DOUBLE_OPERATIONS_H

constexpr double PI = 3.141592653589793238462643383279;
constexpr double ln2 = 0.6931471805599453;
constexpr double doubleEpsilon = 2.220446049250313e-16;

double oAbs(const double a);

int oSgn(const double a);

double oIntPow(double base, const int exp);

double oFact(const int n);

double oNormalizeAngle(double a);

double oSin(double a);

double oCos(double a);

double oTan(const double a);

double oCot(const double a);

double oSec(const double a);

double oCsc(const double a);

double oMin(const double a, const double b);

double oMax(const double a, const double b);

double oClamp(const double a, const double min, const double max);

double oExp(const double x);

double oSqrt(const double a);

double oLn(const double a);

double oPow(const double base, const double exp);

double oLog2(const double a);

double oLog10(const double a);

double oLog(const double base, const double argument);

double oSinH(const double a);

double oCosH(const double a);

double oTanH(const double a);

double oCotH(const double a);

double oSecH(const double a);

double oCscH(const double a);

double oArctan(const double a);

#endif
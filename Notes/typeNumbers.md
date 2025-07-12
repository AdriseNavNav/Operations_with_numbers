# Acerca de los distintos tipos de datos numéricos en este proyecto

Este documento describe la implementación de tipos de datos numéricos siguiendo el estándar **IEEE 754** así como los tipos definidos en este proyecto.

---

## Índice
- [Double](#double)
  - [Estructura](#estructura)
  - [Algoritmo de conversión](#algoritmo-de-conversión)
  - [Ejemplos](#ejemplos)
  - [Rango](#rango)
  - [Precisión](#precisión)

---

## Double

Un dato `x` de tipo `double` se puede declarar con la siguiente sintaxis:

```cpp
double x;
```

Así mismo, es posible darle distintos tipos de valores numéricos:

```cpp
double x = 1;
double y = 1.3;
double z = -5.0;
```

### Estructura

Los `double` son esencialmente `float` de precisión extendida, se representan con una cadena de 64 bits como 00000000000000000000000000000000 o 10100100000100000000100000010000. En particular, cualquier cadena de 64 bits tiene un valor `double` asociado, aunque no todos ellos son valores numéricos.

Para calcular el valor de un `double` de acuerdo a su representación binaria debemos entender las partes abstractas que conforman su cadena:

**Signo**: Ocupa el primer bit de la cadena, si el `double` corresponde a un valor numérico entonces un 0 representa el signo positivo y un 1 el negativo. En el estándar **IEEE-754** se distingue -0 de +0 aunque tienen el mismo valor ante comparaciones `==`.

**Exponente**: Ocupa del bit 2 al 12, corresponde a un número entero positivo 0, 1, ... , 2047. Se dice que el exponente de un `double` esta en formato sesgado pues no corresponde al valor real.

**Mantisa**: Ocupa del bit 13 al 64, corresponde a un número decimal. A continuación veremos como se determina su valor.

### Algoritmo de conversión

Dadas estas partes podemos encontrar el valor de cualquier cadena de 64 bits correspondiente a un `double` con el siguiente algoritmo:

Le asignamos el entero correspondiente a la cadena en base dos del exponente a una variable entera `E`. Notemos que `E` es 0 si la cadena es solo 0 y 2047 si es solo 1.

Tomamos la posición de cada 1 en la mantisa:

$$
p_1, \quad p_2, \quad ... \quad , \quad p_n
$$

A una variable decimal `F` le asignamos:

$$
F = \sum_{i = 1}^{n} 2^{-p_i}
$$

A una variable entera `G` le damos el valor que tenga la cadena signo (0 o 1).

**Caso 1**: Si el exponente no es igual a 0 y no es igual a 2047:

El valor es de tipo numérico (normal) y es igual a:

$$
\text{Valor} = (-1)^{\text{G}} \times 2^{\text{E} - 1023} \times \left( 1.0 + \text{F} \right)
$$

**Caso 2**: Si el exponente es igual a 0:

**Caso 2.1**: Si, además, la mantisa es una cadena de solo 0, entonces el valor será de tipo numérico (normal) con +0 si el signo es 0 y -0 si es 1.

**Caso 2.2**: Si, por el contrario, la mantisa no es una cadena de solo 0, entonces el valor sera de tipo numérico (subnormal) y es igual a:

$$
\text{Valor} = (-1)^{\text{G}} \times 2^{ - 1022} \times \text{F}
$$

**Caso 3**: Si el exponente es igual a 2047:

**Caso 3.1**: Si, además, la mantisa es una cadena de solo 1, entonces el valor será de tipo numérico con +$\infty$ si el signo es 0 y -$\infty$ si es 1.

**Caso 3.2**: Si, por el contrario, la mantisa no es una cadena de solo 1, entonces el valor sera de tipo `NaN`. Aunque existen recomendaciones y distinciones entre los valores `sNaN` y `qNaN` los detalles se escapan de los fines de este documento.

### Ejemplos

El número uno:

$0 \quad 01111111111 \quad  0000000000000000000000000000000000000000000000000000$
$+ \quad \quad 2^{1023 - 1023} \quad \times \quad ( 1.0 )$
$= \quad 1.0$

El número mas pequeño mayor a uno:

$0 \quad 01111111111 \quad 0000000000000000000000000000000000000000000000000001$
$+ \quad \quad 2^{1023 - 1023} \quad \times \quad ( 1.0 + 2^{-52} )$
$= \quad 1.0000000000000002220$

El segundo número mas pequeño mayor a uno:

$0 \quad 01111111111 \quad 0000000000000000000000000000000000000000000000000010$
$+ \quad \quad 2^{1023 - 1023} \quad \times \quad ( 1.0 + 2^{-51} )$
$= \quad 1.0000000000000004441$

El número dos:

$0 \quad 10000000000 \quad 0000000000000000000000000000000000000000000000000000$
$+ \quad \quad 2^{1024 - 1023} \quad \times \quad ( 1.0 )$
$= \quad 2.0$

El número tres:

$0 \quad 10000000000 \quad 1000000000000000000000000000000000000000000000000000$
$+ \quad \quad 2^{1024 - 1023} \quad \times \quad ( 1.0 + 2^{-1} )$
$= \quad 3.0$

El número menos uno:

$1 \quad 01111111111 \quad 0000000000000000000000000000000000000000000000000000$
$- \quad \quad 2^{1023 - 1023} \quad \times \quad ( 1.0 )$
$= \quad -1.0$

Aproximación de un tercio:

$0 \quad 01111111101 \quad 0101010101010101010101010101010101010101010101010101$
$+ \quad \quad 2^{2046 - 1023} \quad \times \quad ( 1.0 + 2^{-2} + 2^{-4} + . . . + 2^{-52} )$
$= \quad 0.33333333333333331483$

Aproximación de PI:

$0 \quad 10000000000 \quad 1001001000011111101101010100010001000010110100011000$
$= \quad 3.141592653589793116$

El número normal positivo mas pequeño:

$0 \quad 00000000001 \quad 0000000000000000000000000000000000000000000000000001$
$+ \quad \quad 2^{1 - 1023} \quad \times \quad ( 1.0 )$
$= \quad 2.2250738585072014 × 10^{−308}$

El número normal mas grande:

$0 \quad 11111111110 \quad 1111111111111111111111111111111111111111111111111111$
$+ \quad \quad 2^{2046 - 1023} \quad \times \quad ( 1.0 + 2^{-1} + 2^{-2} + . . . + 2^{-52} )$
$= \quad 1.7976931348623157 × 10^{308}$

El número subnormal positivo mas pequeño:

$0 \quad 00000000000 \quad 0000000000000000000000000000000000000000000000000001$
$+ \quad \quad 2^{-1022} \quad \times \quad ( 2^{-52} )$
$=  \quad 4.9406564584124654 × 10^{−324}$

El número subnormal mas grande:

$0 \quad 00000000000 \quad 1111111111111111111111111111111111111111111111111111$
$+ \quad \quad 2^{-1022} \quad \times \quad ( 2^{-1} + 2^{-2} + . . . + 2^{-52} )$
$= \quad 2.2250738585072009 × 10^{-308}$

El cero positivo:

$0 \quad 00000000000 \quad 0000000000000000000000000000000000000000000000000000$
$+ \quad \quad 2^{-1022} \quad \times \quad ( 0.0 )$
$= \quad +0.0$

El cero negativo:

$1 \quad 00000000000 \quad 0000000000000000000000000000000000000000000000000000$
$- \quad \quad 2^{-1022} \quad \times \quad ( 0.0 )$
$= \quad -0.0$

El infinito positivo:

$0 \quad 11111111111 \quad 0000000000000000000000000000000000000000000000000000$
$= \quad + \infty$

El infinito negativo:

$1 \quad 11111111111 \quad 0000000000000000000000000000000000000000000000000000$
$= \quad - \infty$

Valor no numérico (`sNaN`):

$0 \quad 11111111111 \quad 0000000000000000000000000000000000000000000000000001$
$= \quad \text{NaN}$

Valor no numérico (`qNaN`):

$0 \quad 11111111111 \quad 1000000000000000000000000000000000000000000000000001$
$= \quad \text{NaN}$

Valor no numérico (`qNaN`):

$0 \quad 11111111111 \quad 1111111111111111111111111111111111111111111111111111$
$= \quad \text{NaN}$

### Rango

Los valores numéricos posibles de un `double` comprenden el intervalo desde -1.7976931348623157 × 10^308 hasta 1.7976931348623157 × 10^308 para números normales. Mientras que para números subnormales se extiende desde -2.2250738585072009 × 10^-308 hasta 2.2250738585072009 × 10^-308.

### Precisión

Aunque los `double` parezcan engañosamente precisos, ya que entre el 1.0 y el siguiente valor posible 1.0000000000000002220 existe una diferencia de tan solo 2.22 × 10^-16 que asegura 15 decimales correctos, realmente su precisión se pierde cuanto mayor es el valor del número sin signo. Por ejemplo, si compilas y ejecutas el siguiente código:

```cpp
#include <iostream>
#include <iomanip>

int main() {

    double x = 9007199254740992.0;
    double y = x + 1.0;

    std::cout << std::setprecision(20);
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    return 0;

}
```

Obtendrás el siguiente resultado:

```
x = 9007199254740992
y = 9007199254740992
```

Lo cual es evidentemente incorrecto, o al menos lo es si tu objetivo es imprimir el sucesor 9007199254740992.

A partir de ahora analizaremos lo que sucede con los números normales y por practicidad el caso positivo.

Dado un número normal `double` `x` sabemos que debe encontrarse en el rango que proporciona este tipo de datos, además, tenemos una fórmula para calcular su valor en función de su cadena. Esta misma fórmula permite estimar el número mas pequeño y mayor a `x` que llamaremos `y`, analicemos esto un poco:

Si elegimos asignarle a `y` como exponente el sucesor del exponente `E` de `x`, por construcción, esto puede provocar un cambio muy grande en el rango de valores posibles para `y` que sería de (2^`E + 1`, 2^`E + 2`) mientras que el de `x`es (2^`E`, 2^`E + 1`), por lo que esto solo sería posible si la mantisa de `x` son solo 1 y la de `y` solo 0.

El enfoque correcto es asignarle a `y` el sucesor de la mantisa de `x`, aumentando el exponente si se da el caso anterior. De este modo, si `F` corresponde al valor de la mantisa, `F + 2^-52` será el sucesor de acuerdo a su definición y la de suma binaria. Aplicando esto a una fórmula:

$$
y = 2^{\text{E} - 1023} \times ( 1.0 + \text{F} + 2^{-52} ) = x + 2^{\text{E} - 1023 - 52 }
$$

Si consideramos que el exponente real `e` es `E - 1023`, el margen entre ambos valores será:

$$
y -  x = 2^{e - 52}
$$

Además, de la definición de `x` como número normal `double` se tiene: 

$$
e = \left\lfloor \log_2 \left| x \right| \right\rfloor
$$

Por lo que nuestra función de margen entre un número `double` `x` y su mayor mas cercano es:

$$
M(x) = 2^{ \left\lfloor \log_2 \left| x \right| \right\rfloor - 52}
$$

La cual admite negativos debido al valor absoluto. Así, el número de decimales correctos de un `double` `x` corresponde a la parte entero del negativo del logaritmo en base diez de nuestra función margen:

$$
D(x) = \left\lfloor \log_{10}  \left( 2^{ \left\lfloor \log_2 \left| x \right| \right\rfloor - 52} \right) \right\rfloor
$$

En particular, para 9007199254740992 ese valor es de -1. Para interpretar este resultado debemos considerar que un valor de 2 indicaría que un número es preciso hasta su centésimas, para 1 tendríamos garantía hasta sus decímas, con 0 serían sus unidades y para -1 solo tenemos asegurado el valor de las decenas. De este modo, cualquier valor entre 9007199254740992 y 9007199254741002 podría ser indistinguible, afortunadamente esto solo nos da la garantía pues si se compila y ejecuta el siguiente codigo:

```cpp
#include <iostream>
#include <iomanip>

int main() {

    double x = 9007199254740992.0;

    std::cout << std::setprecision(20);
    std::cout << "x = " << x << std::endl;

    for(int i = 1; i <= 10; i++) {

        x = 9007199254740992.0 + i;

        std::cout << "x + " << i << " = " << x << std::endl;

    }

    return 0;

}
```

Imprimirá el siguiente resultado:

```
x = 9007199254740992
x + 1 = 9007199254740992
x + 2 = 9007199254740994
x + 3 = 9007199254740996
x + 4 = 9007199254740996
x + 5 = 9007199254740996
x + 6 = 9007199254740998
x + 7 = 9007199254741000
x + 8 = 9007199254741000
x + 9 = 9007199254741000
x + 10 = 9007199254741002
```

Donde se puede observar como todos los números impares son imposibles de representar en este rango, si avanzamos a valores aún mayor veremos como solo los enteros multiplicados por alguna potencia de dos se pueden representar.

Veamos en que intervalo de valores podemos tener determinada cantidad de decimales correctos:

<table style="border-collapse: collapse; width: 100%;">
  <tr>
    <th style="border: 1px solid #ddd; padding: 8px; text-align: center;">Decimales correctos</th>
    <th style="border: 1px solid #ddd; padding: 8px; text-align: center;">Intervalo</th>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">15</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-8 < x < 8</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">14</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-64 < x < 64</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">13</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-512 < x < 512</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">12</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-8192 < x < 8192</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">11</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-65536 < x < 65536</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">10</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-5.24288e+5 < x < 5.24288e+5</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">9</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-8.388608e+6 < x < 8.388608e+6</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">8</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-6.710886e+7 < x < 6.710886e+7</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">7</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-5.368709e+8 < x < 5.368709e+8</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">6</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-8.589934e+9 < x < 8.589934e+9</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">5</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-6.871947e+10 < x < 6.871947e+10</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">4</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-5.497558e+11 < x < 5.497558e+11</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">3</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-8.796093e+12 < x < 8.796093e+12</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">2</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-7.036874e+13 < x < 7.036874e+13</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">1</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-5.629499e+14 < x < 5.629499e+14</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">0</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-9.007199e+15 < x < 9.007199e+15</td>
  </tr>
  <tr>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-1</td>
    <td style="border: 1px solid #ddd; padding: 8px; text-align: center;">-7.205759e+16 < x < 7.205759e+16</td>
  </tr>
</table> 
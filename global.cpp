/*
 * Copyright 2011 Victor Manuel Fernandez Castro.
 * vmfdez90@gmail.com
 *
 * Este archivo forma parte de "Curva de Bezier".
 *
 * "Curva de Bezier" es software libre: usted puede redistribuirlo y/o
 * modificarlo bajo los terminos de la Licencia Publica General de GNU publicada
 * por la Free Software Foundation, bien de la version 3 de la Licencia, o de
 * (a su eleccion) cualquier version posterior.
 *
 * Este programa se distribuye con la esperanza de que sea util, pero SIN
 * NINGUNA GARANTIA; incluso sin la garantia implicita de COMERCIABILIDAD o
 * IDONEIDAD PARA UN PROPOSITO PARTICULAR. Vease la Licencia Publica General de
 * GNU para mas detalles.
 *
 * Usted deberia haber recibido una copia de la Licencia Publica General de GNU
 * junto con este programa. Si no, vease <http://gnu.org/licenses/>.
 */

#include "global.h"
#include <cmath>

// Distribucion binomial
#define binomial(n, i) (factorial(n) / (factorial(i) * factorial(n - i)))

//------------------------------------------------------------------------------
// Polinomio de Bernstein

double bernstein(int i, int n, double t)
{
    return binomial(n, i) * pow(t, i) * pow(1 - t, n - i);
}

//------------------------------------------------------------------------------
// Funcion Factorial

double factorial(double n)
{
    double fact = 1.0;

    for (int i = 2; i <= n; i++)
        fact *= i;

    return fact;
}

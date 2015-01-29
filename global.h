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

#ifndef GLOBAL_H
#define GLOBAL_H

// Polinomio de Bernstein
double bernstein(int i, int n, double t);

// Funcion Factorial
double factorial(double n);

#define MINIMUM_SIZE 640, 480   // Longitud y anchura minimas de la ventana

#define FIRST_POINT QPoint(width() / 8, height() / 8)           // Primer punto
#define LAST_POINT QPoint(width() * 7 / 8, height() * 7 / 8)    // Ultimo punto

#define NPOINTS_BEZIER  10000   // Numero de puntos en que dividimos la curva
#define NPOINTS_WEIGHTS 2000    // Numero de puntos de las graficas de peso
#define WEIGHTS_HEIGHT  200     // Altura de las graficas de peso

#define HELPTEXT_PEN QPen(Qt::black, 1.0)                   // Texto de ayuda
#define DRAWPOINTS_PEN QPen(Qt::black, 5.0)                 // Puntos
#define DRAWCONTROL_PEN QPen(Qt::gray, 1.0, Qt::DashLine)   // Poligonal
#define DRAWWEIGHTS_PEN QPen(Qt::green, 1.0)                // Lineas de peso
#define DRAWSELWEIGHT_PEN QPen(Qt::red, 2.0)                // Linea de peso sel
#define DRAWBEZIER_COLOR Qt::blue                           // Color de la curva
#define DRAWBEZIER_TICK 2.0                                 // Grosor

#define MAX_POINTS 50           // Numero de puntos maximo
#define POINT_TOLLERANCE 5      // Tolerancia respecto a los puntos de control
#define PARAM_TOLLERANCE 0.1    // Tolerancia respecto a la poligonal

#endif // GLOBAL_H

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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>
#include <QStack>

class Widget : public QWidget
{
    Q_OBJECT

public:

    // Constructor
    Widget(QWidget *parent = 0);

protected:

    // Evento de apertura de ventana
    void showEvent(QShowEvent *);

    // Evento de dibujado
    void paintEvent(QPaintEvent *);

    // Evento de boton del raton pulsado
    void mousePressEvent(QMouseEvent *event);

    // Evento de boton del raton soltado
    void mouseReleaseEvent(QMouseEvent *event);

    // Evento de movimiento del raton
    void mouseMoveEvent(QMouseEvent *event);

    // Evento de tecla pulsada
    void keyPressEvent(QKeyEvent *event);

private:
    QList<QPoint> points;   // Lista de todos los puntos
    QStack<int> newPoints;  // Pila de puntos nuevos
    QColor curveColor;      // Color de la curva
    int iSelected;          // Indice del punto seleccionado
    bool showHelp;          // Mostrar cuadro de ayuda?
    bool showControlLines;  // Mostrar poligonal de control?
    bool showWeightLines;   // Mostras lineas de peso?

    // Punto perteneciente a la curva de Bezier en funcion del parametro
    QPoint bezier(double t);

    // Evalua si un punto pertenece al segmento entre otros dos
    bool belongs(const QPoint &point, int iPoint1, int iPoint2);

    // Exporta la curva a un archivo
    void exportCurve();
};

#endif // WIDGET_H

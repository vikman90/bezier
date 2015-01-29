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

#include "widget.h"
#include "global.h"
#include <QIcon>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QColorDialog>

//------------------------------------------------------------------------------
// Constructor

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    iSelected = -1;
    showHelp = showControlLines = showWeightLines = true;
    curveColor = DRAWBEZIER_COLOR;

    setMinimumSize(MINIMUM_SIZE);
    setWindowTitle("Curva de Bezier - by VikMan's");
    setWindowIcon(QIcon(":/bezier.png"));
}

//------------------------------------------------------------------------------
// Evento de apertura de ventana

void Widget::showEvent(QShowEvent *)
{
    points << FIRST_POINT << LAST_POINT;
}

//------------------------------------------------------------------------------
// Evento de dibujado

void Widget::paintEvent(QPaintEvent *)
{
    static const double DIFT_BEZIER = 1.0 / NPOINTS_BEZIER;
    static const double DIFT_WEIGHTS = 1.0 / NPOINTS_WEIGHTS;
    const int n = points.size() - 1;

    QPainter painter(this);

    // Cuadro de ayuda

    if (showHelp) {
#ifdef Q_WS_WIN
        painter.setPen(HELPTEXT_PEN);
        painter.drawText(5, 12, "Click izqdo: Crear/mover punto de control.");
        painter.drawText(5, 24, "Click dcho: Borrar punto de control.");
        painter.drawText(5, 36, "Escape: Quitar ultimo punto introducido.");
        painter.drawText(5, 48, "F1: Mostrar/ocultar esta ayuda.");
        painter.drawText(260, 12, "F2: Mostrar/ocultar poligonal de control.");
        painter.drawText(260, 24, "F3: Mostrar/ocultar lineas de peso.");
        painter.drawText(260, 36, "F4: Cambiar color de la curva.");
        painter.drawText(260, 48, "F5: Exportar a un archivo.");
        painter.drawRect(0, 0, 500, 50);
#else
        painter.setPen(HELPTEXT_PEN);
        painter.drawText(5, 12, "Click izqdo: Crear/mover punto de control.");
        painter.drawText(5, 24, "Click dcho: Borrar punto de control.");
        painter.drawText(5, 36, "Escape: Quitar ultimo punto introducido.");
        painter.drawText(5, 48, "F1: Mostrar/ocultar esta ayuda.");
        painter.drawText(300, 12, "F2: Mostrar/ocultar poligonal de control.");
        painter.drawText(300, 24, "F3: Mostrar/ocultar lineas de peso.");
        painter.drawText(300, 36, "F4: Cambiar color de la curva.");
        painter.drawText(300, 48, "F5: Exportar a un archivo.");
        painter.drawRect(0, 0, 580, 50);
#endif // Q_WS_WIN
    }

    // Puntos de control

    painter.setPen(DRAWPOINTS_PEN);

    for (int i = n; i >= 0; i--)
        painter.drawPoint(points[i]);

    // Poligonal de control

    if (showControlLines) {
        painter.setPen(DRAWCONTROL_PEN);

        for (int i = n - 1; i >= 0; i--)
            painter.drawLine(points[i], points[i + 1]);
    }

    // Lineas de peso

    if (showWeightLines) {
        painter.setPen(DRAWWEIGHTS_PEN);

        for (int i = n; i >= 0; i--)
            if (i != iSelected)
                for (double t = 0.0; t <= 1.0; t += DIFT_WEIGHTS)
                    painter.drawPoint((int)(width() * t), (int)(bernstein(i, n, t) * (-WEIGHTS_HEIGHT) + height()));

        // La linea de peso seleccionada se dibja sobre del resto

        if (iSelected >= 0) {
            painter.setPen(DRAWSELWEIGHT_PEN);

            for (double t = 0.0; t <= 1.0; t += DIFT_WEIGHTS)
                painter.drawPoint((int)(width() * t), (int)(bernstein(iSelected, n, t) * (-WEIGHTS_HEIGHT) + height()));
        }
    }

    // Curva de Bezier

    painter.setPen(QPen(curveColor, DRAWBEZIER_TICK));

    for (double t = 0.0; t <= 1.0; t += DIFT_BEZIER)
        painter.drawPoint(bezier(t));

}

//------------------------------------------------------------------------------
// Evento de boton del raton pulsado

void Widget::mousePressEvent(QMouseEvent *event)
{
    // Seleccionar para mover/borrar puntos

    for (int i = points.size() - 1; i >= 0; i--) {
        if (qAbs(points[i].x() - event->x()) < POINT_TOLLERANCE && qAbs(points[i].y() - event->y()) < POINT_TOLLERANCE) {
            if (event->button() == Qt::LeftButton) {
                iSelected = i;
                update();
            }
            else if (event->button() == Qt::RightButton && i != 0 && i != points.size() - 1) {
                points.removeAt(i);
                update();
            }

            return;
        }
    }

    // Crear un punto en la poligonal de control

    if (event->button() != Qt::LeftButton || points.size() == MAX_POINTS)
        return;

    for (int i = points.size() - 1; i >= 1; i--) {
        if (belongs(event->pos(), i - 1, i)) {
            points.insert(i, event->pos());
            newPoints.push(i);
            iSelected = i;
            update();
            break;
        }
    }
}

//------------------------------------------------------------------------------
// Evento de boton del raton soltado

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        iSelected = -1;
        update();
    }
}

//------------------------------------------------------------------------------
// Evento de movimiento del raton

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton && iSelected >= 0) {
        points[iSelected] = event->pos();
        update();
    }
}

//------------------------------------------------------------------------------
// Evento de tecla pulsada

void Widget::keyPressEvent(QKeyEvent *event)
{
    int iPoint;

    switch (event->key()) {
    case Qt::Key_Escape:

        if (!newPoints.empty()) {
            iPoint = newPoints.pop();
            points.removeAt(iPoint);

            if (iPoint == iSelected)
                iSelected = -1;

            update();
        }
        break;

    case Qt::Key_F1:
        showHelp = !showHelp;
        update();
        break;

    case Qt::Key_F2:
        showControlLines = !showControlLines;
        update();
        break;

    case Qt::Key_F3:
        showWeightLines = !showWeightLines;
        update();
        break;

    case Qt::Key_F4:
        curveColor = QColorDialog::getColor(curveColor, this, "Seleccione color");
        update();
        break;

    case Qt::Key_F5:
        exportCurve();
    }
}

//------------------------------------------------------------------------------
// Punto perteneciente a la curva de Bezier en funcion del parametro

QPoint Widget::bezier(double t)
{
    const int n = points.size() - 1;
    QPointF sum;

    for (int i = 0; i <= n; i++)
        sum += QPointF(points[i]) * bernstein(i, n, t);

    return sum.toPoint();
}

//------------------------------------------------------------------------------
// Evalua si un punto pertenece al segmento entre otros dos

bool Widget::belongs(const QPoint &point, int iPoint1, int iPoint2)
{
    const QPoint &a = points.at(iPoint1);
    const QPoint &b = points.at(iPoint2);
    double tx, ty;
    bool irresolvableTx = false, irresolvableTy = false;

    if (qAbs(b.x() - a.x()) <= POINT_TOLLERANCE) // Linea vertical
        irresolvableTx = true;
    else
        tx = (double)(point.x() - a.x()) / (b.x() - a.x());

    if (qAbs(b.y() - a.y()) <= POINT_TOLLERANCE) // Linea horizontal
        irresolvableTy = true;
    else
        ty = (double)(point.y() - a.y()) / (b.y() - a.y());

    if (irresolvableTx && irresolvableTy)
        return true;
    else if (irresolvableTx)
        return ty > 0.0 && ty < 1.0 && qAbs(a.x() - point.x()) < POINT_TOLLERANCE;
    else if (irresolvableTy)
        return tx > 0.0 && tx < 1.0 && qAbs(a.y() - point.y()) < POINT_TOLLERANCE;
    else
        return tx > 0.0 && tx < 1.0 && qAbs(tx - ty) < PARAM_TOLLERANCE;
}

//------------------------------------------------------------------------------
// Exporta la curva a un archivo

void Widget::exportCurve()
{
    static const double DIFT_BEZIER = 1.0 / NPOINTS_BEZIER;
    static const double DIFT_WEIGHTS = 1.0 / NPOINTS_WEIGHTS;
    const int n = points.size() - 1;

    QString fileName = QFileDialog::getSaveFileName(this, "Guardar archivo", QDir::homePath(), "Imagenes (*.bmp *.gif *.jpg *.jpeg *.png);;Todos los archivos (*.*)");
    QImage image(size(), QImage::Format_RGB32);
    QPainter painter;

    image.fill(QColor(Qt::white).rgb());
    painter.begin(&image);

    // Puntos de control

    painter.setPen(DRAWPOINTS_PEN);

    for (int i = n; i >= 0; i--)
        painter.drawPoint(points[i]);

    // Poligonal de control

    if (showControlLines) {
        painter.setPen(DRAWCONTROL_PEN);

        for (int i = n - 1; i >= 0; i--)
            painter.drawLine(points[i], points[i + 1]);
    }

    // Lineas de peso

    if (showWeightLines) {
        painter.setPen(DRAWWEIGHTS_PEN);

        for (int i = n; i >= 0; i--)
            if (i != iSelected)
                for (double t = 0.0; t <= 1.0; t += DIFT_WEIGHTS)
                    painter.drawPoint((int)(width() * t), (int)(bernstein(i, n, t) * (-WEIGHTS_HEIGHT) + height()));

        // La linea de peso seleccionada se dibja sobre del resto

        if (iSelected >= 0) {
            painter.setPen(DRAWSELWEIGHT_PEN);

            for (double t = 0.0; t <= 1.0; t += DIFT_WEIGHTS)
                painter.drawPoint((int)(width() * t), (int)(bernstein(iSelected, n, t) * (-WEIGHTS_HEIGHT) + height()));
        }
    }

    // Curva de Bezier

    painter.setPen(QPen(curveColor, DRAWBEZIER_TICK));

    for (double t = 0.0; t <= 1.0; t += DIFT_BEZIER)
        painter.drawPoint(bezier(t));

    painter.end();
    image.save(fileName);
}

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

#include <QApplication>
#include "widget.h"

//------------------------------------------------------------------------------
// Funcion principal

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget widget;
    widget.show();

    return app.exec();
}

/*
Copyright Romha Korev and dimitry Ernot (2020-03-30)

romha [dot] korev [at] gmail [dot] com
ernd [dot] mail [at] gmail [dot] com

This software is a computer program whose purpose is to provide a Design System for Qt Applications.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
*/

#include <QApplication>
#include <QQuickWidget>
#include <QQmlContext>

#include <QtWidgets>



#include "../controlers/colorpicker/qml/colorpickerqml.h"
#include "../controlers/colorpicker/widgets/colorpicker.h"
#include "../indicators/gauges/pumpkin_gauges.h"

#include "../indicators/sevensegments/sevensegmentsml.h"
#include "../indicators/sevensegments/symbol.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


	QApplication app(argc, argv);

	qmlRegisterAnonymousType<Brushes>("", 1);
	qmlRegisterType<VerticalGaugeQML>("pumpkin.gauges", 1, 0, "VerticalGauge");
	qmlRegisterType<CircularGaugeQML>("pumpkin.gauges", 1, 0, "CircularGauge");
	qmlRegisterType<CircularGaugeQML>("pumpkin.gauges", 1, 0, "CircularGauge");
	qmlRegisterType<ColorPickerQML>("pumpkin.controlers", 1, 0, "ColorPicker");
	qmlRegisterType<SevenSegmentsML>("pumpkin.indicators", 1, 0, "SevenSegments");


	Pumpkin::VerticalGauge* verticalGaugeWidget = new Pumpkin::VerticalGauge();
	Pumpkin::CircularGauge* circularGaugeWidget = new Pumpkin::CircularGauge();
	Pumpkin::ColorPicker* colorPicker = new Pumpkin::ColorPicker();

	QWidget* widgets = new QWidget();
	QGridLayout* grid = new QGridLayout(widgets);
	grid->addWidget(verticalGaugeWidget);
	grid->addWidget(circularGaugeWidget);
	grid->addWidget(colorPicker);

	QQuickWidget *view = new QQuickWidget;
	view->rootContext()->setContextProperty("verticalGaugeWidget", verticalGaugeWidget);
	view->rootContext()->setContextProperty("circularGaugeWidget", circularGaugeWidget);
	view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));


	QWidget* gallery = new QWidget();
	widgets->setFixedWidth(200);
	QHBoxLayout* layout = new QHBoxLayout(gallery);
	layout->addWidget(view);
	layout->addWidget(widgets);
	gallery->show();

	return app.exec();
}

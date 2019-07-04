#include <QApplication>
#include <QQuickWidget>
#include <QtWidgets>
#include <QQmlContext>

#include "../gauges/pumpkin_gauges.h"
#include "../spinners/spinner.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	qmlRegisterType<Brushes>();
	qmlRegisterType<VerticalGaugeQML>("pumpkin.gauges", 1, 0, "VerticalGauge");
	qmlRegisterType<CircularGaugeQML>("pumpkin.gauges", 1, 0, "CircularGauge");
	qmlRegisterType<CircularGaugeQML>("pumpkin.gauges", 1, 0, "CircularGauge");
	qmlRegisterType<Spinner>("pumpkin.spinners", 1, 0, "Spinner");



	/*QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;*/

	Pumpkin::VerticalGauge* verticalGaugeWidget = new Pumpkin::VerticalGauge();
	Pumpkin::CircularGauge* circularGaugeWidget = new Pumpkin::CircularGauge();

	QWidget* widgets = new QWidget();
	QGridLayout* grid = new QGridLayout(widgets);
	grid->addWidget(verticalGaugeWidget);
	grid->addWidget(circularGaugeWidget);

	QQuickWidget *view = new QQuickWidget;
	view->rootContext()->setContextProperty("verticalGaugeWidget", verticalGaugeWidget);
	view->rootContext()->setContextProperty("circularGaugeWidget", circularGaugeWidget);
	view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));


	QWidget* gallery = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout(gallery);
	layout->addWidget(view);
	layout->addWidget(widgets);
	gallery->show();

	return app.exec();
}

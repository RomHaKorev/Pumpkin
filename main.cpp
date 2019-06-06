#include <QApplication>
#include <QQuickWidget>
#include <QtWidgets>
#include <QQmlContext>

#include "qml/verticalgaugeqml.h"

#include "widgets/verticalgauge.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	qmlRegisterType<Brushes>();
	qmlRegisterType<VerticalGaugeQML>("pumpkin.gauges", 1, 0, "VerticalGauge");



	/*QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;*/

	Pumpkin::VerticalGauge* verticalGaugeWidget = new Pumpkin::VerticalGauge();

	QWidget* widgets = new QWidget();
	QGridLayout* grid = new QGridLayout(widgets);
	grid->addWidget(verticalGaugeWidget);

	QQuickWidget *view = new QQuickWidget;
	view->rootContext()->setContextProperty("verticalGaugeWidget", verticalGaugeWidget);
	view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));


	QWidget* gallery = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout(gallery);
	layout->addWidget(view);
	layout->addWidget(widgets);
	gallery->show();

	return app.exec();
}

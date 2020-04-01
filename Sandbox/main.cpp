#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQmlContext>

#include "verticaltreelayout.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qmlRegisterType<VerticalTreeLayout>("pumpkin.tree", 1, 0, "TreeView");

	QStandardItemModel* model = new QStandardItemModel();
	auto* a = new QStandardItem("A");
	auto* b = new QStandardItem("B");
	auto* c = new QStandardItem("C");
	auto* d = new QStandardItem("D");
	auto* e = new QStandardItem("E");
	auto* f = new QStandardItem("F");
	auto* g = new QStandardItem("G");
	auto* h = new QStandardItem("H");
	auto* i = new QStandardItem("I");
	auto* j = new QStandardItem("J");
	auto* k = new QStandardItem("K");
	auto* l = new QStandardItem("L");
	auto* m = new QStandardItem("M");
	auto* n = new QStandardItem("N");
	auto* o = new QStandardItem("O");

	d->appendRows(QList<QStandardItem*>() << b << c);
	e->appendRows(QList<QStandardItem*>() << a << d);
	m->appendRows(QList<QStandardItem*>() << h << i << j << k << l);
	n->appendRows(QList<QStandardItem*>() << g << m);
	o->appendRows(QList<QStandardItem*>() << e << f << n);

	//root->appendRows(QList<QStandardItem*>() << new QStandardItem("Leaf #1") << new QStandardItem("Leaf #2"));
	model->appendRow(o);

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("myModel", model);
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

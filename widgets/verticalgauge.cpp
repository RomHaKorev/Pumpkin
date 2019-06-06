#include "verticalgauge.h"

#include <QDebug>

Pumpkin::VerticalGauge::VerticalGauge(QWidget *parent) : QWidget(parent),
	renderer(new VerticalGaugeRenderer<Pumpkin::VerticalGauge>(this))
{
	init();
	resize(40, 120);
	setValue(0);
	setMinimum(0);
	setMaximum(100);
	connect(this, &VerticalGauge::valueChanged, [=](qreal o, qreal n) {qDebug() << Q_FUNC_INFO << o << n; });
}


void Pumpkin::VerticalGauge::paintEvent(QPaintEvent* event)
{
	QRectF const contentsRect(QRectF(QPointF(0, 0), size()).adjusted(2, 2, -2, -2));
	QPainter painter(this);
	renderer->paint(painter, contentsRect);
}

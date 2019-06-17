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
}


void Pumpkin::VerticalGauge::paintEvent(QPaintEvent* event)
{
	QRectF const contentsRect(QRectF(QPointF(0, 0), size()).adjusted(2, 2, -2, -2));
	QPainter painter(this);
	renderer->paint(painter, contentsRect);
}

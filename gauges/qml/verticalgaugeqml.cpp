#include "verticalgaugeqml.h"

#include "../renderers/verticalgaugerenderer.h"

VerticalGaugeQML::VerticalGaugeQML(QQuickItem* parent): QQuickPaintedItem (parent),
	renderer(new VerticalGaugeRenderer<VerticalGaugeQML>(this))
{
	init();
	setSize(QSizeF(40, 120));
}


QRectF VerticalGaugeQML::boundingRect() const
{
	return QRectF(QPointF(0, 0), size());
}


QRectF const VerticalGaugeQML::contentsBoundingRect() const
{
	return boundingRect().adjusted(2, 2, -2, -2);
}


void VerticalGaugeQML::paint(QPainter* painter)
{
	renderer->paint(*painter, contentsBoundingRect());
}

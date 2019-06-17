#include "circulargaugeqml.h"


#include "../renderers/circulargaugerenderer.h"

CircularGaugeQML::CircularGaugeQML(QQuickItem* parent): QQuickPaintedItem (parent),
  renderer(new CircularGaugeRenderer<CircularGaugeQML>(this))
{
  init();
  setSize(QSizeF(120, 120));
}


QRectF CircularGaugeQML::boundingRect() const
{
  return QRectF(QPointF(0, 0), size());
}


QRectF const CircularGaugeQML::contentsBoundingRect() const
{
  return boundingRect().adjusted(2, 2, -2, -2);
}


void CircularGaugeQML::paint(QPainter* painter)
{
  renderer->paint(*painter, contentsBoundingRect());
}

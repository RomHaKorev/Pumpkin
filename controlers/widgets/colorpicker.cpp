#include "colorpicker.h"

#include <QDebug>

Pumpkin::ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent),
	renderer(new ColorPickerRenderer<Pumpkin::ColorPicker>(this))
{
	resize(120, 120);
}


void Pumpkin::ColorPicker::paintEvent(QPaintEvent* /*event*/)
{
	QRectF const contentsRect(QPointF(0, 0), size());
	QPainter painter(this);
	renderer->paint(painter, contentsRect);
}

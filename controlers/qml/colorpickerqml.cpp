#include "colorpickerqml.h"

#include "../renderers/colorpickerrenderer.h"

ColorPickerQML::ColorPickerQML(QQuickItem* parent): QQuickPaintedItem (parent)//,
	//renderer(new ColorPickerRenderer<ColorPickerQML>(this))
{
	setSize(QSizeF(120, 120));
	init();
	setAcceptedMouseButtons(Qt::LeftButton);
	m_color = Qt::red;
}


QRectF ColorPickerQML::boundingRect() const
{
	return QRectF(QPointF(0, 0), size());
}

QRectF const ColorPickerQML::hueBoundingRect() const
{
	QRectF const r = boundingRect();

	qreal const heightWoBrightnessPart = r.height() - 24;
	qreal const w = std::min(r.width(), heightWoBrightnessPart);
	return QRectF(boundingRect().center() - QPointF(w/2, w/2 + 20), QSizeF(w, w)).adjusted(16, 16, -16, -16);
}

QLineF const ColorPickerQML::brightnessBoundingLine() const
{
	QRectF const contentRect = hueBoundingRect();
	return QLineF(contentRect.left(), contentRect.bottom() + 20, contentRect.right(), contentRect.bottom() + 20);
}


void ColorPickerQML::paint(QPainter* p)
{

	QColor white = QColor(240, 240, 240);
	if (m_color.saturation() < 75)
		white = Qt::lightGray;
	QRectF const contentRect = hueBoundingRect();
	QPainter& painter = *p;
	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(color());
	painter.drawRect(boundingRect());

	QColor c(white);
	c.setAlpha(90);
	painter.setBrush(Qt::NoBrush);
	painter.setPen(QPen(c, 4));
	painter.drawEllipse(contentRect);

	painter.drawLine(brightnessBoundingLine());

	painter.setBrush(white);
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(hueRect());
	painter.drawEllipse(okRect());
	painter.setPen(m_color);
	QFont font("Helvetica", 14, 2);
	font.setBold(true);
	painter.setFont(font);
	painter.drawText(okRect(), Qt::AlignCenter, "OK");

	painter.drawEllipse(brightnessRect());
	painter.restore();
	painter.drawRect(hueBoundingRect());
}

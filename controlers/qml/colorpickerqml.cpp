#include "colorpickerqml.h"

#include "../renderers/colorpickerrenderer.h"

QRectF const ColorPickerQML::cursorSize = QRectF(-20, -20, 40, 40);

ColorPickerQML::ColorPickerQML(QQuickItem* parent): QQuickPaintedItem (parent),
	checkmarkAnimation(new QVariantAnimation(this)),
	textAnimation(new QVariantAnimation(this)),
	sequentialAnimation(new QSequentialAnimationGroup(this))
	//renderer(new ColorPickerRenderer<ColorPickerQML>(this))
{
	sequentialAnimation->addAnimation(checkmarkAnimation);
	sequentialAnimation->addAnimation(textAnimation);
	checkmarkAnimation->setStartValue(0.0);
	checkmarkAnimation->setEndValue(1.0);
	textAnimation->setStartValue(0.0);
	textAnimation->setEndValue(1.0);
	checkmarkAnimation->setDuration(750);
	textAnimation->setDuration(750);

	connect(checkmarkAnimation, &QVariantAnimation::valueChanged, this, [=]() { update(okRect().toRect()); });
	connect(textAnimation, &QVariantAnimation::valueChanged, this, [=]() { update(okRect().toRect()); });

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

	qreal const heightWoBrightnessPart = r.height() - cursorSize.width();
	qreal const w = std::min(r.width(), heightWoBrightnessPart);
	qreal const offset = cursorSize.width();
	return QRectF(boundingRect().center() - QPointF(w/2, w/2 + 20), QSizeF(w, w)).adjusted(offset, offset, -offset, -offset);
}

QLineF const ColorPickerQML::brightnessBoundingLine() const
{
	QRectF const contentRect = hueBoundingRect();
	return QLineF(contentRect.left(), contentRect.bottom() + cursorSize.width(), contentRect.right(), contentRect.bottom() + cursorSize.width());
}


void ColorPickerQML::paint(QPainter* p)
{
	QColor const white = QColor(240, 240, 240);
	QColor borderWhite = white.darker(110);
	borderWhite.setAlpha(120);
	QColor lightColor;
	lightColor.setHsv(m_color.hue(), 255, 255, 120);

	QRectF const contentRect = hueBoundingRect();
	QPainter& painter = *p;
	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::black);
	painter.drawRect(boundingRect());
	painter.setBrush(lightColor);
	painter.drawRect(boundingRect());

	painter.setBrush(color());
	painter.setPen(QPen(borderWhite, 4));
	painter.drawEllipse(contentRect);

	painter.drawLine(brightnessBoundingLine());


	painter.setPen(Qt::NoPen);
	painter.setBrush(borderWhite);
	painter.drawEllipse(okRect().adjusted(-4, -4, 4, 4));
	painter.setBrush(white);
	painter.drawEllipse(okRect());
	painter.setPen(m_color);
	QFont font("Helvetica", 14, 2);
	font.setBold(true);
	painter.setFont(font);

	if (sequentialAnimation->state() == QSequentialAnimationGroup::Running)
	{


		QRectF const r = okRect().adjusted(10, 10, -10, -10);
		qreal const x = r.width()/7;
		qreal const y = r.height()/5;
		QPainterPath p;
		p.moveTo(0, y * 2);
		p.lineTo(3 * x, 5 * y);
		p.lineTo(7 * x, 0);
		painter.setPen(QPen(m_color, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		QRectF clipRect(okRect());
		clipRect.setWidth(clipRect.width() * checkmarkAnimation->currentValue().toReal());
		painter.setClipRect(clipRect);
		painter.setOpacity(1.0 - textAnimation->currentValue().toReal());
		painter.drawPath(p.translated(r.topLeft()));
		painter.setOpacity(textAnimation->currentValue().toReal());
		painter.drawText(okRect(), Qt::AlignCenter, "OK");
	}
	else
		painter.drawText(okRect(), Qt::AlignCenter, "OK");

	painter.setPen(Qt::NoPen);
	painter.setBrush(borderWhite);
	painter.drawEllipse(brightnessRect());
	painter.drawEllipse(hueRect());
	painter.setBrush(white);
	painter.drawEllipse(brightnessRect().adjusted(6, 6, -6, -6));
	painter.drawEllipse(hueRect().adjusted(6, 6, -6, -6));

	painter.restore();
}

#ifndef COLORPICKERRENDERER_H
#define COLORPICKERRENDERER_H

#include <QObject>
#include <QPainter>
#include <QDebug>

#include <QVariantAnimation>
#include <QSequentialAnimationGroup>

template<typename T> class ColorPickerRenderer : public QObject
{
public:
	ColorPickerRenderer(T* parent): QObject(parent), parent(parent)
	{
	}

	void paint(QPainter& painter, QRectF const& contentRect)
	{
		/*painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(Qt::NoPen);
		painter.setBrush(parent->color());
		painter.drawRect(contentRect);

		painter.setBrush(Qt::NoBrush);
		painter.setPen(QPen(Qt::white, 8));
		painter.drawEllipse(contentRect.adjusted(20, 20, -20, -20));

		painter.setBrush(Qt::white);
		painter.setPen(Qt::NoPen);
		painter.drawEllipse(parent.cursorAngle());*/
	}


	T* parent;
	QBrush backgroundBrush;
	QBrush foregroundBrush;
	QPen boderPen;
};

#endif // COLORPICKERRENDERER_H

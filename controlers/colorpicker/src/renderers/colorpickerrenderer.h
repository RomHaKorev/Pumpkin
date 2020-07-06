/*
Copyright Romha Korev and dimitry Ernot (2020-03-30)

romha [dot] korev [at] gmail [dot] com
ernd [dot] mail [at] gmail [dot] com

This software is a computer program whose purpose is to provide a Design System for Qt Applications.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
*/
#ifndef COLORPICKERRENDERER_H
#define COLORPICKERRENDERER_H

#include <QObject>
#include <QPainter>
#include <QDebug>

#include <QVariantAnimation>
#include <QSequentialAnimationGroup>
#include <QPainterPath>


#include "colorpickeranimator.h"
//#include "colorpickerbase.h"


class ColorPickerRendererBase
{
public:
	QRectF const cursorSize = QRectF(-20, -20, 40, 40);
	virtual QRectF boundingRect() const = 0;
	virtual QRectF const hueBoundingRect() const = 0;
	virtual QLineF const brightnessBoundingLine() const = 0;
	virtual QRectF hueRect() const = 0;
	virtual QRectF okRect() const = 0;
	virtual QRectF brightnessRect() const = 0;
	virtual void paint(QPainter& painter) = 0;
	virtual void restartButtonAnimation() = 0;

	virtual ~ColorPickerRendererBase() = default;
};

template<typename T> class ColorPickerRenderer : public QObject, public ColorPickerRendererBase
{
public:
	ColorPickerRenderer(T* parent): QObject(parent), parent(parent),
		animator(new ColorPickerAnimator())
	{
		QObject::connect(animator->checkmarkAnimation, &QVariantAnimation::valueChanged, parent, [=]() { parent->update(okRect().toRect()); });
		connect(animator->textAnimation, &QVariantAnimation::valueChanged, parent, [=]() { parent->update(okRect().toRect()); });
	}

	virtual ~ColorPickerRenderer()
	{
		animator->deleteLater();
	}

	QRectF boundingRect() const
	{
		return QRectF(QPointF(0, 0), parent->size());
	}

	QRectF const hueBoundingRect() const
	{
		QRectF const r = boundingRect();

		qreal const heightWoBrightnessPart = r.height() - cursorSize.width();
		qreal const w = std::min(r.width(), heightWoBrightnessPart);
		qreal const offset = cursorSize.width();
		return QRectF(boundingRect().center() - QPointF(w/2, w/2 + 20), QSizeF(w, w)).adjusted(offset, offset, -offset, -offset);
	}

	QLineF const brightnessBoundingLine() const
	{
		QRectF const contentRect = hueBoundingRect();
		return QLineF(contentRect.left(), contentRect.bottom() + cursorSize.width(), contentRect.right(), contentRect.bottom() + cursorSize.width());
	}

	virtual QRectF hueRect() const
	{
		QRectF const r = hueBoundingRect();
		QLineF distance(r.center(), QPointF(r.center().x() + r.width()/2, r.center().y()));
		distance.setAngle(parent->color().hue());
		return cursorSize.translated(distance.p2());
	}

	virtual QRectF okRect() const
	{
		return QRectF(-24, -24, 48, 48).translated(hueBoundingRect().center());
	}

	virtual QRectF brightnessRect() const
	{
		qreal const sat = parent->color().valueF();
		QLineF l(brightnessBoundingLine());
		l.setLength(l.length() * sat);
		return cursorSize.translated(l.p2());
	}


	void paint(QPainter& painter)
	{
		QColor const white = QColor(240, 240, 240);
		QColor borderWhite = white.darker(110);
		borderWhite.setAlpha(120);
		QColor lightColor;
		lightColor.setHsv(parent->color().hue(), 255, 255, 120);

		QRectF const& contentRect = hueBoundingRect();
		painter.save();
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(Qt::NoPen);

		painter.setBrush(parent->color());
		painter.setPen(QPen(borderWhite, 4));
		painter.drawEllipse(contentRect);

		painter.drawLine(brightnessBoundingLine());

		painter.setPen(Qt::NoPen);
		painter.setBrush(borderWhite);
		painter.drawEllipse(okRect().adjusted(-4, -4, 4, 4));
		painter.setBrush(white);
		painter.drawEllipse(okRect());
		painter.setPen(parent->color());
		QFont font("Helvetica", 14, 2);
		font.setBold(true);
		painter.setFont(font);

		if (animator->sequentialAnimation->state() == QSequentialAnimationGroup::Running)
		{
			QRectF const r = okRect().adjusted(10, 10, -10, -10);
			qreal const x = r.width()/7;
			qreal const y = r.height()/5;
			QPainterPath p;
			p.moveTo(0, y * 2);
			p.lineTo(3 * x, 5 * y);
			p.lineTo(7 * x, 0);
			painter.setPen(QPen(parent->color(), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			QRectF clipRect(okRect());
			clipRect.setWidth(clipRect.width() * animator->checkmarkAnimation->currentValue().toReal());
			painter.setClipRect(clipRect);
			painter.setOpacity(1.0 - animator->textAnimation->currentValue().toReal());
			painter.drawPath(p.translated(r.topLeft()));
			painter.setOpacity(animator->textAnimation->currentValue().toReal());
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

	void restartButtonAnimation() {
		animator->restartButtonAnimation();
	}
private:
	T* parent;
	QBrush backgroundBrush;
	QBrush foregroundBrush;
	QPen boderPen;

	ColorPickerAnimator* animator;
};

#endif // COLORPICKERRENDERER_H

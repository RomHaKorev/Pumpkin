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

#ifndef COLORPICKERQML_H
#define COLORPICKERQML_H

#include <QQuickPaintedItem>
#include <QTime>
#include <QLineF>
#include <QBrush>
#include <QVariantAnimation>
#include <QSequentialAnimationGroup>

#include "../colorpickercommon.h"

template<typename T> class ColorPickerRenderer;

class ColorPickerQML : public QQuickPaintedItem
{
	Q_OBJECT
	COLORPICKER_INTERFACE
	static QRectF const cursorSize;
public:
	ColorPickerQML(QQuickItem* parent=nullptr);
	virtual ~ColorPickerQML() override {}

	virtual QRectF boundingRect() const override;
	inline QRectF const hueBoundingRect() const;
	inline QLineF const brightnessBoundingLine() const;
	virtual void paint(QPainter* painter) override;

	virtual QRectF hueRect() const
	{
		QRectF const r = hueBoundingRect();
		QLineF distance(r.center(), QPointF(r.center().x() + r.width()/2, r.center().y()));
		distance.setAngle(color().hue());
		return cursorSize.translated(distance.p2());
	}

	virtual QRectF okRect() const
	{
		return QRectF(-24, -24, 48, 48).translated(hueBoundingRect().center());
	}

	virtual QRectF brightnessRect() const
	{
		qreal const sat = m_color.valueF();
		QLineF l(brightnessBoundingLine());
		l.setLength(l.length() * sat);
		return cursorSize.translated(l.p2());
	}

	virtual void mousePressEvent(QMouseEvent* event) override
	{
		lastPressTime.restart();
		if (hueRect().contains(event->pos()))
			moveHueCursor = true;
		else if (brightnessRect().contains(event->pos()))
			moveBrightnessCursor = true;

	}

	virtual void mouseMoveEvent(QMouseEvent* event) override
	{
		if (moveHueCursor)
		{
			QLineF distance(hueBoundingRect().center(), event->pos());
			m_color.setHsv(int(distance.angle()), m_color.value(), m_color.value());
			update();
		}
		else if (moveBrightnessCursor)
		{
			QPointF eventPosition(std::max(qreal(brightnessBoundingLine().x1()), qreal(event->pos().x())), event->pos().y());
			QLineF distance(brightnessBoundingLine().p1(), QPointF(eventPosition.x(), brightnessBoundingLine().y1()));
			qreal const saturation = (distance.length() / brightnessBoundingLine().length()) * 240;
			qreal const bounded = std::max(std::min(saturation, 240.0), 0.0);
			m_color.setHsv(m_color.hue(), m_color.saturation(), int(bounded));
			update();
		}
	}

	virtual void mouseReleaseEvent(QMouseEvent* event) override
	{
		moveHueCursor = false;
		moveBrightnessCursor = false;
		if (lastPressTime.elapsed() < 200)
			click(event->pos());
	}
private:
	void click(QPointF const& position)
	{
		if (!okRect().contains(position))
			return;
		validate();
		if (okRect().contains(position))
		{
			sequentialAnimation->setCurrentTime(0);
			sequentialAnimation->stop();
			sequentialAnimation->start();
		}
	}

	void validate()
	{
		colorChanged(m_color);
	}

private:
	bool moveHueCursor, moveBrightnessCursor;
	QVariantAnimation* checkmarkAnimation;
	QVariantAnimation* textAnimation;
	QSequentialAnimationGroup* sequentialAnimation;
	QTime lastPressTime;
};

#endif // COLORPICKERQML_H

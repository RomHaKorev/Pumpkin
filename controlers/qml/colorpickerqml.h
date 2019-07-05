#ifndef COLORPICKERQML_H
#define COLORPICKERQML_H

#include <QQuickPaintedItem>
#include <QTime>
#include <QLineF>

#include "../colorpickercommon.h"

template<typename T> class ColorPickerRenderer;

class ColorPickerQML : public QQuickPaintedItem
{
	Q_OBJECT
	COLORPICKER_INTERFACE
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
		return QRectF(-8, -8, 16, 16).translated(distance.p2());
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
		return QRectF(-8, -8, 16, 16).translated(l.p2());
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
			qDebug() << distance << bounded << distance.length() << brightnessBoundingLine().length() << bounded;
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
	bool moveHueCursor, moveBrightnessCursor;
	QTime lastPressTime;

	void click(QPointF const& position)
	{
		if (okRect().contains(position))
			validate();
	}

	void validate()
	{
		colorChanged(m_color);
	}
};

#endif // COLORPICKERQML_H

#ifndef CIRCULARGAUGEQML_H
#define CIRCULARGAUGEQML_H

#include <QQuickPaintedItem>

#include <QBrush>
#include "../gaugeinterface.h"

template<typename T> class CircularGaugeRenderer;

class CircularGaugeQML : public QQuickPaintedItem
{
	Q_OBJECT
	GAUGE_INTERFACE(qreal)
public:
	CircularGaugeQML(QQuickItem* parent=nullptr);

	virtual QRectF boundingRect() const override;
	inline QRectF const contentsBoundingRect() const;
	virtual void paint(QPainter* painter) override;
	CircularGaugeRenderer<CircularGaugeQML>* renderer;
};
#endif // CIRCULARGAUGEQML_H

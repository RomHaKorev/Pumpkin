#ifndef VERTICALGAUGEQML_H
#define VERTICALGAUGEQML_H

#include <QQuickPaintedItem>
#include <QBrush>

#include "../gaugeinterface.h"

template<typename T> class VerticalGaugeRenderer;

class VerticalGaugeQML : public QQuickPaintedItem
{
	Q_OBJECT
	GAUGE_INTERFACE(qreal)
public:
	VerticalGaugeQML(QQuickItem* parent=nullptr);
	virtual ~VerticalGaugeQML() override {}

	virtual QRectF boundingRect() const override;
	inline QRectF const contentsBoundingRect() const;
	virtual void paint(QPainter* painter) override;
	VerticalGaugeRenderer<VerticalGaugeQML>* renderer;
};

#endif // VERTICALGAUGEQML_H

#ifndef CIRCULARGAUGE_H
#define CIRCULARGAUGE_H

#include <QWidget>

#include "../gaugeinterface.h"
#include "../renderers/circulargaugerenderer.h"

namespace Pumpkin {
class CircularGauge : public QWidget
{
	Q_OBJECT
	GAUGE_INTERFACE(qreal)

public:
	explicit CircularGauge(QWidget *parent = nullptr);
	virtual void paintEvent(QPaintEvent* event) override;

	virtual QSize sizeHint() const override { return QSize(40, 120); }

private:
	CircularGaugeRenderer<Pumpkin::CircularGauge>* renderer;
};
}

#endif // CIRCULARGAUGE_H

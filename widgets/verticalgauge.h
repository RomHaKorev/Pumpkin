#ifndef VERTICALGAUGE_H
#define VERTICALGAUGE_H

#include <QWidget>

#include "../core/gaugeinterface.h"
#include "../core/verticalgaugerenderer.h"

namespace Pumpkin {
class VerticalGauge : public QWidget
{
	Q_OBJECT
	GAUGE_INTERFACE(qreal)

public:
	explicit VerticalGauge(QWidget *parent = nullptr);
	virtual void paintEvent(QPaintEvent* event) override;

	virtual QSize sizeHint() const override { return QSize(40, 120); }

private:
	VerticalGaugeRenderer<Pumpkin::VerticalGauge>* renderer;
};
}

#endif // VERTICALGAUGE_H

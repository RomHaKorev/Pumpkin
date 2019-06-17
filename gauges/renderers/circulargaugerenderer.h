#ifndef VERTICALGAUGERENDERER_H
#define VERTICALGAUGERENDERER_H

#include <QObject>
#include <QPainter>
#include <QDebug>

#include <QVariantAnimation>
#include <QSequentialAnimationGroup>

template<typename T> class CircularGaugeRenderer : public QObject
{
public:
	CircularGaugeRenderer(T* parent): QObject(parent), parent(parent),
		disturbanceAnimation(new QVariantAnimation(this)),
		valueAnimation(new QVariantAnimation(this)),
		sequentialAnimation(new QSequentialAnimationGroup(this))
	{
		disturbanceAnimation->setDuration(2000);
		disturbanceAnimation->setEasingCurve(QEasingCurve::OutBounce);

		disturbanceAnimation->setStartValue(0.0);
		//disturbanceAnimation->setKeyValueAt(0.5, 20.0);
		disturbanceAnimation->setEndValue(0.0);

		sequentialAnimation->addAnimation(valueAnimation);
		sequentialAnimation->addAnimation(disturbanceAnimation);

		connect(valueAnimation, &QVariantAnimation::valueChanged, this, [=]() { parent->update(); });
		connect(disturbanceAnimation, &QVariantAnimation::valueChanged, this, [=]() { parent->update(); });

		connect(parent, &T::valueChanged, this, &CircularGaugeRenderer::restartAnimation);
	}

	void paint(QPainter& painter, QRectF const& contentRect)
	{
		qreal const animatedValue = valueAnimation->currentValue().toReal();
		qreal const disturbedAngle = this->disturbanceAnimation->currentValue().toDouble();
		qreal const angle = (180.0 * animatedValue / (parent->maximum() - parent->minimum())) + disturbedAngle;

		qreal const thickness = std::min(contentRect.width(), contentRect.height()) / 4.0;
		QRectF const arcRect(contentRect.adjusted(thickness/2, thickness/2, -thickness/2, -thickness/2));

		painter.save();
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QPen(parent->style()->background(), thickness/2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
		painter.drawArc(arcRect, (180.0 - angle) * 16.0, -(180.0 - angle) * 16.0);
		painter.setPen(QPen(parent->style()->foreground(), thickness/2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
		painter.drawArc(arcRect, 180.0 * 16.0, -angle * 16.0);
		painter.restore();
	}

private:
	void restartAnimation(qreal oldValue, qreal newValue)
	{
		qreal const h = std::min(qAbs(newValue - oldValue) * 100.0 / (parent->maximum() - parent->minimum()), 20.0);

		disturbanceAnimation->setKeyValueAt(0.2, h);

		valueAnimation->setStartValue(valueAnimation->currentValue().toReal());
		valueAnimation->setEndValue(parent->value());
		valueAnimation->stop();
		disturbanceAnimation->stop();
		sequentialAnimation->start();
	}

	T* parent;
	QVariantAnimation* disturbanceAnimation;
	QVariantAnimation* valueAnimation;
	QSequentialAnimationGroup* sequentialAnimation;
};

#endif // VERTICALGAUGERENDERER_H

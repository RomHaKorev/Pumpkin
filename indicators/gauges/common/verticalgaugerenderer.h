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

#ifndef VERTICALGAUGERENDERER_H
#define VERTICALGAUGERENDERER_H

#include <QObject>
#include <QPainter>
#include <QDebug>

#include <QVariantAnimation>
#include <QSequentialAnimationGroup>
#include <QPainterPath>

template<typename T> class VerticalGaugeRenderer : public QObject
{
public:
	VerticalGaugeRenderer(T* parent): QObject(parent), parent(parent),
		disturbanceAnimation(new QVariantAnimation(this)),
		valueAnimation(new QVariantAnimation(this)),
		sequentialAnimation(new QSequentialAnimationGroup(this))
	{
		disturbanceAnimation->setDuration(2000);
		disturbanceAnimation->setEasingCurve(QEasingCurve::OutElastic);

		disturbanceAnimation->setStartValue(0.0);
		disturbanceAnimation->setKeyValueAt(0.1, 40.0);
		disturbanceAnimation->setEndValue(0.0);

		sequentialAnimation->addAnimation(valueAnimation);
		sequentialAnimation->addAnimation(disturbanceAnimation);

		connect(valueAnimation, &QVariantAnimation::valueChanged, this, [=]() { parent->update(); });
		connect(disturbanceAnimation, &QVariantAnimation::valueChanged, this, [=]() { parent->update(); });

		connect(parent, &T::valueChanged, this, &VerticalGaugeRenderer::restartAnimation);
	}

	void paint(QPainter& painter, QRectF const& contentRect)
	{
		qreal const animatedValue = valueAnimation->currentValue().toReal();
		qreal const y = contentRect.height() - (contentRect.height() / (parent->maximum() - parent->minimum())) * animatedValue + contentRect.y();

		painter.save();
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(Qt::NoPen);

		QPainterPath clipPath;
		if (parent->style()->rounded())
			clipPath.addRoundedRect(contentRect, 100.0, contentRect.width()/contentRect.height() * 100.0, Qt::RelativeSize);
		else
			clipPath.addRect(contentRect);
		painter.setBrush(parent->style()->background());
		painter.setClipPath(clipPath);
		painter.drawPath(clipPath);

		QPointF const p1(contentRect.x(), y);
		QPointF const p2(contentRect.x() + contentRect.width(), y);

		qreal const disturbedY = this->disturbanceAnimation->currentValue().toDouble();
		QPointF const pCtrl1(contentRect.x() + contentRect.width() / 4.0, y + disturbedY);
		QPointF const pCtrl2(contentRect.x() + 3.0 * contentRect.width() / 4.0, y - disturbedY);
		QPainterPath path;
		path.moveTo(contentRect.bottomLeft());
		path.lineTo(p1);
		path.cubicTo(pCtrl1, pCtrl2, p2);
		path.lineTo(contentRect.bottomRight());
		path.closeSubpath();

		painter.setBrush(parent->style()->foreground());
		painter.drawPath(path);
		painter.restore();
	}

private:
	void restartAnimation(qreal oldValue, qreal newValue)
	{
		qreal const h = std::min(qAbs(newValue - oldValue) * 100.0 / (parent->maximum() - parent->minimum()), 40.0);

		disturbanceAnimation->setKeyValueAt(0.1, h);

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
	QBrush backgroundBrush;
	QBrush foregroundBrush;
	QPen boderPen;
};

#endif // VERTICALGAUGERENDERER_H

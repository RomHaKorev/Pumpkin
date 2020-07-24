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

#ifndef GAUGEINTERFACE_H
#define GAUGEINTERFACE_H

#include <QObject>
#include <QBrush>

class Brushes: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
	Q_PROPERTY(QColor background READ background WRITE setBackground)
	Q_PROPERTY(bool rounded READ rounded WRITE setRounded)

public:
	Brushes(QObject* parent=nullptr): QObject(parent),
		backgroundBrush(QColor(30, 40, 42)),
		foregroundBrush(QColor(0, 194, 173))
	{}
	inline QColor const& foreground() const { return foregroundBrush; }
	inline QColor const& background() const { return backgroundBrush; }
	inline bool const& rounded() const { return roundedValue; }

public slots:
	void setForeground(QColor const& value) { foregroundBrush = value; }
	void setBackground(QColor const& value) { backgroundBrush = value; }
	void setRounded(bool value) { roundedValue = value; }
signals:
	void changed();

private:
	QColor backgroundBrush, foregroundBrush;
	bool roundedValue;
};


Q_DECLARE_METATYPE(Brushes*)

#define GAUGE_INTERFACE(type) \
	Q_PROPERTY(Brushes* style READ style) \
	Q_PROPERTY(type value READ value WRITE setValue) \
	Q_PROPERTY(type minimum READ minimum WRITE setMinimum) \
	Q_PROPERTY(type maximum READ maximum WRITE setMaximum) \
	Q_PROPERTY(QBrush progressBrush READ progressBrush WRITE setProgressBrush) \
	Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush) \
public: \
	inline type value() const { return m_value; } \
	inline type minimum() const { return minimumValue; } \
	inline type maximum() const { return maximumValue; } \
	Q_SLOT void setValue(type newValue) \
	{ \
		qreal const currentValue = m_value; \
		m_value = newValue; \
		emit valueChanged(currentValue, m_value);  \
	} \
	Q_SLOT void setMinimum(type value) \
	{ \
		minimumValue = value; \
		if (m_value < minimumValue) \
			setValue(minimumValue); \
	} \
	Q_SLOT void setMaximum(type value) \
	{ \
		maximumValue = value; \
		if (m_value > maximumValue) \
			setValue(maximumValue); \
	} \
	Q_SIGNAL void valueChanged(type oldValue, type newValue); \
	inline QBrush progressBrush() const { return progressBrushValue; } \
	Q_SLOT void setProgressBrush(QBrush const& value) { progressBrushValue = value; } \
	inline QBrush backgroundBrush() const { return backgroundBrushValue; } \
	Q_SLOT void setBackgroundBrush(QBrush const& value) { backgroundBrushValue = value; } \
	inline Brushes* style() { return brushesContainer; } \
private: \
	Brushes* brushesContainer; \
	type m_value, minimumValue, maximumValue; \
	QBrush progressBrushValue, backgroundBrushValue; \
	void init() { brushesContainer = new Brushes(this); m_value = 0; minimumValue = 0; maximumValue = 100; }

#endif // GAUGEINTERFACE_H

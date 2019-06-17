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

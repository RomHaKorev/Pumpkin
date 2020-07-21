#ifndef COLORPICKERCOMMON_H
#define COLORPICKERCOMMON_H

#include <QObject>

/*#define COLORPICKER_INTERFACE \
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorEdited) \
	Q_PROPERTY(int brightness READ brightness WRITE setBrightness) \
public: \
	static QRectF const cursorSize; \
	inline QColor color() const { return m_color; } \
	inline int brightness() const { return m_color.saturation(); } \
	Q_SLOT void setColor(QColor const& newValue) \
	{ \
		m_color = newValue; \
		emit colorChanged(m_color);  \
		update(); \
	} \
	Q_SLOT void setBrightness(int newValue) \
	{ \
		m_color.setHsv(m_color.hue(), newValue, m_color.value()); \
		emit colorChanged(m_color);  \
		update(); \
	} \
	Q_SIGNAL void colorChanged(QColor const& newValue); \
	Q_SIGNAL void colorEdited(QColor const& newValue); \
private: \
	QColor m_color; \
	QPointF cursorPosition; \
	void init() { cursorPosition = QPointF(60, 20); }*/

#define COLORPICKER_INTERFACE \
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged) \
	Q_PROPERTY(int brightness READ brightness WRITE setBrightness) \
public: \
	Q_SLOT virtual void setColor(QColor const& newValue) override \
    { \
	    ColorPickerBase::setColor(newValue); \
	    emit colorChanged(color());  \
	    update(); \
	} \
	Q_SLOT virtual void setBrightness(int newValue) override \
    { \
	    ColorPickerBase::setBrightness(newValue); \
	    emit colorChanged(color());  \
	    update(); \
	} \
	Q_SIGNAL void colorChanged(QColor const& newValue);


#endif // GAUGEINTERFACE_H




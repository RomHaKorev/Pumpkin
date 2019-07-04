#ifndef COLORPICKERCOMMON_H
#define COLORPICKERCOMMON_H

#include <QObject>

#define COLORPICKER_INTERFACE \
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorEdited) \
	Q_PROPERTY(unsigned int brightness READ brightness WRITE setBrightness) \
public: \
	inline QColor color() const { return m_color; } \
	inline unsigned int brightness() const { return m_color.saturation(); } \
	Q_SLOT void setColor(QColor const& newValue) \
    { \
	    m_color = newValue; \
	    emit colorChanged(m_color);  \
	    update(); \
	} \
	Q_SLOT void setBrightness(unsigned int newValue) \
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
	void init() { cursorPosition = QPointF(60, 20); }

#endif // GAUGEINTERFACE_H


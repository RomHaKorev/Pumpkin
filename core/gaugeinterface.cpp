#include "gaugeinterface.h"

GaugeInterface::GaugeInterface(QObject* parent)
{}

void GaugeInterface::setMinimum(qreal value)
{
	minimumValue = value;
	if (m_value < minimumValue)
		setValue(minimumValue);
}

void GaugeInterface::setMaximum(qreal value)
{
	maximumValue = value;
	if (m_value > maximumValue)
		setValue(maximumValue);
}

qreal GaugeInterface::value() const
{
	return m_value;
}

void GaugeInterface::setValue(qreal value)
{
	qreal const currentValue = m_value;
	m_value = value;
	emit valueChanged(currentValue, m_value);
}

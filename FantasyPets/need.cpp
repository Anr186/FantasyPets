#include "need.h"
#include <QtGlobal>

Need::Need(const QString& name, int maxValue)
    : m_name(name), m_value(maxValue), m_maxValue(maxValue)
{
}

double Need::getPercentage() const
{
    if (m_maxValue == 0) return 0.0;
    return (static_cast<double>(m_value) / m_maxValue) * 100.0;
}

void Need::setValue(int value)
{
    m_value = qBound(0, value, m_maxValue);
}

void Need::increase(int amount)
{
    m_value = std::min(m_value + amount, m_maxValue);
}

void Need::decrease(int amount)
{
    m_value = std::max(m_value - amount, 0);
}

bool Need::isCritical() const
{
    return getPercentage() < 20.0;
}

bool Need::isLow() const
{
    return getPercentage() < 50.0;
}


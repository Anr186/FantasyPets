#ifndef NEED_H
#define NEED_H

#include <QString>

class Need
{
public:
    Need(const QString& name, int maxValue = 100);
    
    QString getName() const { return m_name; }
    int getValue() const { return m_value; }
    int getMaxValue() const { return m_maxValue; }
    double getPercentage() const;
    
    void setValue(int value);
    void increase(int amount);
    void decrease(int amount);
    
    bool isCritical() const; // Потребность критична (< 20%)
    bool isLow() const; // Потребность низкая (< 50%)

private:
    QString m_name;
    int m_value;
    int m_maxValue;
};

#endif // NEED_H



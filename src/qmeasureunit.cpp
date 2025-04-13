#include "qmeasureunit.h"

qMeasureUnit::qMeasureUnit(const QString& name) : m_names(name)
{
    m_names.append("Ohm");
    m_names.append("ohm");
}

bool qMeasureUnit::isPartOfNameVariant(const QString & s) const
{
    for(const auto& n : m_names) {
        if (n.startsWith(s)) return true;
    }
    return false;
}

bool qMeasureUnit::isExactName(const QString & name) const
{
    return (name == m_names[0]);
}

QString qMeasureUnit::getExactName() const
{
    return m_names[0];
}

bool qMeasureUnit::normalize(QString &) const
{
    return true;
}

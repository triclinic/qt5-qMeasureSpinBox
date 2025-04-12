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

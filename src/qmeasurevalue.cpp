#include "qmeasurevalue.h"
#include <QRegularExpression>

qMeasureValue::qMeasureValue(int significantFigures) : m_sigfigs(significantFigures), m_delim(',')
{

}

bool qMeasureValue::isPartOfValueString(const QString & str) const
{
    return (str.count(QRegularExpression("\\d")) <= m_sigfigs);
}

bool qMeasureValue::isExactValueString(const QString & str) const
{
    return (str.count(QRegularExpression("\\d")) == m_sigfigs);
}

void qMeasureValue::tidyValueString(QString & target) const
{
    target.replace(QRegularExpression("\\D+"), m_delim);
    if (target.endsWith(m_delim)) target.remove(m_delim);
}

bool qMeasureValue::normalize(QString & rawstr) const
{
    tidyValueString(rawstr);
    int digitCount = rawstr.count(QRegularExpression("\\d"));
    if ( digitCount == 0) {
        rawstr = getDefaultValueString();
        return false;
    }

    return isExactValueString(rawstr);
}

QString qMeasureValue::getDefaultValueString() const
{
    return QString(m_sigfigs + 1, '0').replace(1, 1, m_delim);
}

QChar qMeasureValue::getDelimiter() const
{
    return m_delim;
}

bool qMeasureValue::fixupValueString(const QString &) const
{
    return true;
}

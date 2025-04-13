#ifndef QMEASUREVALUE_H
#define QMEASUREVALUE_H
#include <QString>

class qMeasureValue
{
    int m_sigfigs;
    QChar m_delim;
public:
    qMeasureValue(int significantFigures = 3);

    bool isPartOfValueString(const QString &) const;
    bool isExactValueString(const QString &) const;
    void tidyValueString(QString &) const;
    bool normalize(QString &) const;
    QString getDefaultValueString() const;
    QChar getDelimiter()const;

    virtual ~qMeasureValue() = default;
protected:
    virtual bool fixupValueString(const QString &) const;
};

#endif // QMEASUREVALUE_H

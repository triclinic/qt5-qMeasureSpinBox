#ifndef QMEASUREUNIT_H
#define QMEASUREUNIT_H
#include <QStringList>

class qMeasureUnit
{
    QStringList m_names;
public:
    qMeasureUnit(const QString& = "Ω" );

    bool isPartOfNameVariant(const QString&) const;
};

#endif // QMEASUREUNIT_H

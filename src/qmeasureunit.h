#ifndef QMEASUREUNIT_H
#define QMEASUREUNIT_H
#include <QStringList>

class qMeasureUnit
{
    QStringList m_names;
public:
    qMeasureUnit(const QString& = "Ω" );

    bool isPartOfNameVariant(const QString&) const;
    bool isExactName(const QString&) const;
    QString getExactName() const;
    bool normalize(QString &) const;

    virtual ~qMeasureUnit() = default;
};

#endif // QMEASUREUNIT_H

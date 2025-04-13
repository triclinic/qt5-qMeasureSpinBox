#ifndef QMEASURESPINBOX_H
#define QMEASURESPINBOX_H

#include "qmeasureprefix.h"
#include "qmeasureunit.h"
#include "qmeasurevalue.h"
#include <QAbstractSpinBox>
#include <memory>

class qMeasureSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

    QRegularExpression m_basicPointDelimed, m_basicAnyDelimed;
    std::unique_ptr<qMeasurePrefix> m_prefixService;
    std::unique_ptr<qMeasureUnit> m_unitService;
    std::unique_ptr<qMeasureValue> m_valueService;

    bool isPartOfPrefixUnit(const QString &) const;
    bool isExactPrefixUnit(const QString &) const;
public:
    qMeasureSpinBox(QWidget *parent = nullptr);
signals:
    void valueChanged(double d);
    void valueChanged(const QString &text);
private slots:
    void slotEmitSignals();
    // QAbstractSpinBox interface
public:
    void fixup(QString &input) const;
    QValidator::State validate(QString &input, int &pos) const;
    void stepBy(int steps);
protected:
    StepEnabled stepEnabled() const;
};

#endif // QMEASURESPINBOX_H

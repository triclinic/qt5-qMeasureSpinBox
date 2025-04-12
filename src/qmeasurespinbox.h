#ifndef QMEASURESPINBOX_H
#define QMEASURESPINBOX_H

#include "qmeasureprefix.h"
#include "qmeasureunit.h"
#include <QAbstractSpinBox>
#include <memory>

class qMeasureSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

    QRegularExpression m_basicPointDelimed, m_basicPrefixDelimed;
    std::unique_ptr<qMeasurePrefix> m_prefixService;
    std::unique_ptr<qMeasureUnit> m_unitService;

    bool isPartOfPrefixUnit(const QString &) const;
    bool isPartOfValueString(const QString &) const;
    bool isExactValueString(const QString &) const;
    bool isExactPrefixUnit(const QString &) const;
    void fixupPrefixedValueString(QString &) const;
    bool isExactPrefix(const QString &) const;
    bool isPartOfUnit(const QString &) const;
public:
    qMeasureSpinBox(QWidget *parent = nullptr);


    // QAbstractSpinBox interface
public:
    void fixup(QString &input) const;


    // QAbstractSpinBox interface
public:
    QValidator::State validate(QString &input, int &pos) const;

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    // QAbstractSpinBox interface
public:
    void stepBy(int steps);

protected:
    StepEnabled stepEnabled() const;
};

#endif // QMEASURESPINBOX_H

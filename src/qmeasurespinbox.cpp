#include "qmeasurespinbox.h"
#include <QDebug>
#include <QFocusEvent>
#include <QLineEdit>

/////////////////////////////value only
bool qMeasureSpinBox::isPartOfValueString(const QString & s) const
{
    qDebug() << "isPartOfValueString" << s ;
    return (s.count(QRegularExpression("\\d")) <= 3);
}

bool qMeasureSpinBox::isExactValueString(const QString & s) const
{
    qDebug() << "isExactValueString" << s ;
    return (s.count(QRegularExpression("\\d")) == 3);
}

void qMeasureSpinBox::fixupPrefixedValueString(QString & target) const
{
    target.replace(QRegularExpression("\\D+"), ",");
}



///////////////////////decompose!
bool qMeasureSpinBox::isExactPrefixUnit(const QString & s) const
{
    qDebug() << "isExactPrefixUnit" << s ;
    return true;
}

bool qMeasureSpinBox::isPartOfPrefixUnit(const QString & s) const
{
    qDebug() << "isPartOfPrefixUnit" << s ;
    if (m_prefixService->isPartOfPrefix(s)) return true;
    if (m_prefixService->isCorrectPrefix(s)) {
        //QString choped = m_prefixService->stripPrefix(s);
        // Fixme
    }

    return false;
}


bool qMeasureSpinBox::isExactPrefix(const QString & s) const
{
    return m_prefixService->isCorrectPrefix(s);
}

bool qMeasureSpinBox::isPartOfUnit(const QString & s) const
{
    return m_unitService->isPartOfNameVariant(s);
}

qMeasureSpinBox::qMeasureSpinBox(QWidget *parent) : QAbstractSpinBox(parent)
  , m_prefixService(new qMeasurePrefix)
  , m_unitService(new qMeasureUnit)
{
    m_basicPointDelimed = QRegularExpression(QString("^(?<value>\\d*[,.]?\\d*)(?<spacer>\\s?)(?<prefix_units>\\D*)$") );
    m_basicPrefixDelimed = QRegularExpression(QString("^(?<value>\\d*(?<prefix>\\D{0,2})\\d*)\\s?(?<units>\\D*)$") );
    qDebug() << m_prefixService->getAvailablePrefixStrings() ;
}

void qMeasureSpinBox::fixup(QString &input) const
{
    //qDebug() << "fixup:" << input;
    input = "2.20 µΩ";
}

QValidator::State qMeasureSpinBox::validate(QString &input, int &pos) const
{
    if ( input.contains(m_basicPointDelimed) ) {
        QRegularExpressionMatch m1 = m_basicPointDelimed.match(input);
        QString prefixUnits = m1.captured("prefix_units") ;
        QString valueString = m1.captured("value") ;
        if ( isPartOfValueString(valueString)
             and ( prefixUnits.isEmpty() or isPartOfPrefixUnit(prefixUnits)) )
        {
            if (isExactPrefixUnit(prefixUnits)
                    and not m1.captured("spacer").isEmpty()
                    and isExactValueString(valueString)  )
            {
                return QValidator::State::Acceptable;
            }
            return QValidator::State::Intermediate;
        }

    } else if ( input.contains(m_basicPrefixDelimed) )
        // You can type "2k2" which means 2.2 kOhms.
        // When you are here, the prefix is ​​fully typed.
    {
        QRegularExpressionMatch m2 = m_basicPrefixDelimed.match(input);
        QString prefixString = m2.captured("prefix") ;
        QString valueString = m2.captured("value") ;
        QString unitString = m2.captured("units") ;
        fixupPrefixedValueString(valueString);

        if ( isPartOfValueString(valueString) and isExactPrefix(prefixString)
             and ( unitString.isEmpty() or isPartOfUnit(unitString)) )
        {
            // You need to fixup this string anyway.
            return QValidator::State::Intermediate;
        }
    }
    return QValidator::State::Invalid;
}

void qMeasureSpinBox::focusInEvent(QFocusEvent *event)
{
    //qDebug() << "focusInEvent";
    QAbstractSpinBox::focusInEvent(event);
}

void qMeasureSpinBox::focusOutEvent(QFocusEvent *event)
{
    //qDebug() << "focusOutEvent";
    QAbstractSpinBox::focusOutEvent(event);
}

void qMeasureSpinBox::stepBy(int steps)
{
    qDebug() << "stepBy" << steps;
}

QAbstractSpinBox::StepEnabled qMeasureSpinBox::stepEnabled() const
{
    qDebug() << "stepEnabled";
    return QAbstractSpinBox::StepDownEnabled;
}

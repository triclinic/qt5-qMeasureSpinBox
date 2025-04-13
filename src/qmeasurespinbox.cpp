#include "qmeasurespinbox.h"
#include <QDebug>
#include <QFocusEvent>
#include <QLineEdit>

bool qMeasureSpinBox::isExactPrefixUnit(const QString & s) const
{
    if (m_prefixService->startsWithAlterPrefix(s)) return false;
    QString trimmed = m_prefixService->trimPrefix(s);
    return m_unitService->isExactName(trimmed);
}

bool qMeasureSpinBox::isPartOfPrefixUnit(const QString & s) const
{
    if (m_prefixService->isPartOfPrefix(s)) return true;
    QString trimmed = m_prefixService->trimPrefix(s);
    return m_unitService->isPartOfNameVariant(trimmed);
}

qMeasureSpinBox::qMeasureSpinBox(QWidget *parent) : QAbstractSpinBox(parent)
  , m_prefixService(new qMeasurePrefix)
  , m_unitService(new qMeasureUnit)
  , m_valueService(new qMeasureValue)
{
    m_basicPointDelimed = QRegularExpression(QString("^(?<value>\\d*[%1]?\\d*)(?<spacer>\\s?)(?<prefix_units>\\D*)$").arg(m_valueService->getDelimiter()) );
    m_basicAnyDelimed = QRegularExpression(QString("^(?<value>\\d*(?<delimiter>\\D*)\\d*)\\s?(?<units>\\D*)$") );
    connect(this, SIGNAL(editingFinished()), SLOT(slotEmitSignals()));
    lineEdit()->setText(m_valueService->getDefaultValueString() + " " + m_prefixService->getDefaultPrefix() + m_unitService->getExactName());
}

void qMeasureSpinBox::slotEmitSignals()
{
    interpretText();
    QString res = lineEdit()->text();
    fixup(res);
    //if (res == lineEdit()->text()) return;
    lineEdit()->setText(res);
    qDebug() << "Final text:" << res;
}

void qMeasureSpinBox::fixup(QString &input) const
{
    QRegularExpressionMatch splited = m_basicAnyDelimed.match(input);
    qDebug() << "fixup:" << splited;
    QString resultValueString = splited.captured("value");
    QString resultPrefix;
    if (not m_valueService->normalize(resultValueString)) {
        resultPrefix = m_prefixService->getDefaultPrefix();
    } else {
        QString delimiter = splited.captured("delimiter") ;
        QString units = splited.captured("units") ;
        if (units.isEmpty()) {
            if ( not m_prefixService->tryExtractExactPrefix(delimiter, resultPrefix) ) {
                resultPrefix = m_prefixService->getDefaultPrefix();
            }
        } else {
            if ( not m_prefixService->tryExtractExactPrefix(units, resultPrefix)
                 and not m_prefixService->tryExtractExactPrefix(delimiter, resultPrefix) ) {
                resultPrefix = m_prefixService->getDefaultPrefix();
            }
        }
    }
    input = resultValueString + " " + resultPrefix + m_unitService->getExactName() ;
}

QValidator::State qMeasureSpinBox::validate(QString &input, int &) const
{
    if ( input.contains(m_basicPointDelimed) ) {
        QRegularExpressionMatch m1 = m_basicPointDelimed.match(input);
        QString prefixUnits = m1.captured("prefix_units") ;
        QString valueString = m1.captured("value") ;
        if ( m_valueService->isPartOfValueString(valueString)
             and ( prefixUnits.isEmpty() or isPartOfPrefixUnit(prefixUnits)) )
        {
            if (isExactPrefixUnit(prefixUnits)
                    and not m1.captured("spacer").isEmpty()
                    and m_valueService->isExactValueString(valueString)  )
            {
                return QValidator::State::Acceptable;
            }
            return QValidator::State::Intermediate;
        }

    } else if ( input.contains(m_basicAnyDelimed) )
        // You can type "2k2" which means 2.2 kOhms.
        // When you are here, the prefix is ​​fully typed.
    {
        QRegularExpressionMatch m2 = m_basicAnyDelimed.match(input);
        QString prefixString = m2.captured("delimiter") ;
        QString valueString = m2.captured("value") ;
        QString unitString = m2.captured("units") ;
        m_valueService->tidyValueString(valueString);

        if ( m_valueService->isPartOfValueString(valueString) and m_prefixService->isCorrectPrefix(prefixString)
             and ( unitString.isEmpty() or m_unitService->isPartOfNameVariant(unitString)) )
        {
            // You need to fixup this string anyway.
            return QValidator::State::Intermediate;
        }
    }
    return QValidator::State::Invalid;
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

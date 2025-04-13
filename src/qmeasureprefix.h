#ifndef QMEASUREPREFIX_H
#define QMEASUREPREFIX_H

#include <inttypes.h>
#include <QString>
#include <QMap>
#include <QStringList>

class qMeasurePrefix
{
public:
    enum class Metric : uint32_t {
        None, Deci, Deca, Centi, Hecto
        , Milli, Kilo, Micro, Mega, Nano
        , Giga, Pico, Tera, Femto, Peta
        , Atto, Exa, Zepto, Zetta, Yocto
        , Yotta, Ronto, Ronna, Quecto, Quetta
    };
    qMeasurePrefix(Metric from = Metric::Quecto, Metric to = Metric::Quetta, Metric _default = Metric::Micro);

    QStringList getAvailablePrefixStrings() const;
    qreal getFactorByText(const QString &) const;

    bool isCorrectPrefix(const QString &) const;
    bool isPartOfPrefix(const QString &) const;
    QString trimPrefix(const QString &) const;
    bool startsWithAlterPrefix(const QString &) const;
    bool tryExtractExactPrefix(const QString & from, QString & to) const;
    QString getDefaultPrefix() const;

    virtual ~qMeasurePrefix() = default;
private:
    int getOriginalIndex(int) const;

    struct StdPrefix {
        Metric num;
        QString symbol;
        qreal factor;
        bool isAlter;
    };
    static const struct StdPrefix allPrefixes[];
    QMap<QString, int> m_prefixes;
    int m_default;
    QStringList m_revLexOrderedPrefix;
};

#endif // QMEASUREPREFIX_H

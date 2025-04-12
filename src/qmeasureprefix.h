#ifndef QMEASUREPREFIX_H
#define QMEASUREPREFIX_H

#include <inttypes.h>
#include <QString>
#include <QMap>
class QStringList;

class qMeasurePrefix
{
public:
    enum Metric : uint32_t {
        None = (1u << 0), Deci = (1u << 1), Deca = (1u << 2), Centi = (1u << 3), Hecto = (1u << 4)
        , Milli = (1u << 5), Kilo = (1u << 6), Micro = (1u << 7), Mega = (1u << 8), Nano = (1u << 9)
        , Giga = (1u << 10), Pico = (1u << 11), Tera = (1u << 12), Femto = (1u << 13), Peta = (1u << 14)
        , Atto = (1u << 15), Exa = (1u << 16), Zepto = (1u << 17), Zetta = (1u << 18), Yocto = (1u << 19)
        , Yotta = (1u << 20), Ronto = (1u << 21), Ronna = (1u << 22), Quecto = (1u << 23), Quetta = (1u << 24)
        , Micro_Giga = (Micro | Milli | None | Kilo | Mega | Giga)
    };
    qMeasurePrefix(Metric = Micro_Giga);

    QStringList getAvailablePrefixStrings() const;
    void fixupPrefixString(QString &) const;
    qreal getFactorByText(const QString &) const;

    bool isCorrectPrefix(const QString &) const;
    bool isPartOfPrefix(const QString &) const;
private:
    struct StdPrefix {
        uint32_t flag;
        QString symbol;
        qreal factor;
        bool isAlter;
    };
    static const struct StdPrefix allPrefixes[];
    QMap<QString, int> m_prefixes;
};

#endif // QMEASUREPREFIX_H

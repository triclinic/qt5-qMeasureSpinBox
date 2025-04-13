#include <QtAlgorithms>
#include <QDebug>
#include "qmeasureprefix.h"

const struct qMeasurePrefix::StdPrefix qMeasurePrefix::allPrefixes[] =
{
{qMeasurePrefix::Metric::Quecto, "q",  1.0e-30, false },
{qMeasurePrefix::Metric::Ronto,  "r",  1.0e-27, false },
{qMeasurePrefix::Metric::Yocto,  "y",  1.0e-24, false },
{qMeasurePrefix::Metric::Zepto,  "z",  1.0e-21, false },
{qMeasurePrefix::Metric::Atto,   "a",  1.0e-18, false },
{qMeasurePrefix::Metric::Femto,  "f",  1.0e-15, false },
{qMeasurePrefix::Metric::Pico,   "p",  1.0e-12, false },
{qMeasurePrefix::Metric::Nano,   "n",  1.0e-9,  false },
{qMeasurePrefix::Metric::Micro,  "μ",  1.0e-6,  false },
{qMeasurePrefix::Metric::Micro,  "u",  1.0e-6,  true  },
{qMeasurePrefix::Metric::Milli,  "m",  0.001,   false },
{qMeasurePrefix::Metric::Centi,  "c",  0.01,    false },
{qMeasurePrefix::Metric::Deci,   "d",  0.1,     false },
{qMeasurePrefix::Metric::None,   "",   1.0,     false },
{qMeasurePrefix::Metric::None,   "r",  1.0,     true  },
{qMeasurePrefix::Metric::None,   "R",  1.0,     true  },
{qMeasurePrefix::Metric::Deca,   "da", 10,      false },
{qMeasurePrefix::Metric::Hecto,  "h",  100,     false },
{qMeasurePrefix::Metric::Kilo,   "k",  1000,    false },
{qMeasurePrefix::Metric::Kilo,   "K",  1000,    true  },
{qMeasurePrefix::Metric::Mega,   "M",  1.0e6,   false },
{qMeasurePrefix::Metric::Giga,   "G",  1.0e9,   false },
{qMeasurePrefix::Metric::Tera,   "T",  1.0e12,  false },
{qMeasurePrefix::Metric::Peta,   "P",  1.0e15,  false },
{qMeasurePrefix::Metric::Exa,    "E",  1.0e18,  false },
{qMeasurePrefix::Metric::Zetta,  "Z",  1.0e21,  false },
{qMeasurePrefix::Metric::Yotta,  "Y",  1.0e24,  false },
{qMeasurePrefix::Metric::Ronna,  "R",  1.0e27,  false },
{qMeasurePrefix::Metric::Quetta, "Q",  1.0e30,  false },
};

qMeasurePrefix::qMeasurePrefix(Metric from, Metric to, Metric _default) : m_prefixes()
{
    bool start = false;
    for(int i = 0 ; i < sizeof(allPrefixes) / sizeof(allPrefixes[0]); i++)
    {
        if (allPrefixes[i].num == from) {
            start = true;
            m_default = i;
        }
        if (start){
            if (allPrefixes[i].num == _default) m_default = getOriginalIndex(i);
            m_prefixes[allPrefixes[i].symbol] = i;
            m_revLexOrderedPrefix.append(allPrefixes[i].symbol);
        }
        if (allPrefixes[i].num == to) {
            break;
        }
    }
    qSort(m_revLexOrderedPrefix.begin(), m_revLexOrderedPrefix.end(), std::greater<QString>() );
}

QStringList qMeasurePrefix::getAvailablePrefixStrings() const
{
    return m_revLexOrderedPrefix;
}

qreal qMeasurePrefix::getFactorByText(const QString & p) const
{
    return allPrefixes[ m_prefixes[p] ].factor;
}

bool qMeasurePrefix::isCorrectPrefix(const QString & p) const
{
    return m_prefixes.contains(p);
}

bool qMeasurePrefix::isPartOfPrefix(const QString & s) const
{
    for (const auto& p : m_prefixes) {
        if (allPrefixes[p].symbol.startsWith(s)) return true;
    }
    return false;
}

QString qMeasurePrefix::trimPrefix(const QString & str) const
{
    QString res = str;
    for(const auto& pref : m_revLexOrderedPrefix) {
        if (str.startsWith(pref)) {
            res.remove(0, pref.size());
            break;
        }
    }
    return res;
}

bool qMeasurePrefix::startsWithAlterPrefix(const QString & str) const
{
    for(const auto& pref : m_revLexOrderedPrefix) {
        if (str.startsWith(pref)) {
            return allPrefixes[ m_prefixes[pref] ].isAlter;
        }
    }
    return true;
}

bool qMeasurePrefix::tryExtractExactPrefix(const QString &from, QString &to) const
{
    for(const auto& pref : m_revLexOrderedPrefix) {
        if (from.startsWith(pref)) {
            int index = m_prefixes[pref];
            if (allPrefixes[ index ].isAlter) {
                index = getOriginalIndex(index);
            }
            to = allPrefixes[ index ].symbol;
            return true;
        }
    }
    return false;
}

QString qMeasurePrefix::getDefaultPrefix() const
{
    return allPrefixes[ m_default ].symbol;
}

int qMeasurePrefix::getOriginalIndex(int i) const
{
    while( ( i > 0 ) and allPrefixes[ i ].isAlter ) i--;
    return i;
}


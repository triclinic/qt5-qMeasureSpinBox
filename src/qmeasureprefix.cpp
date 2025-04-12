#include <QStringList>
#include <QDebug>
#include "qmeasureprefix.h"


const struct qMeasurePrefix::StdPrefix qMeasurePrefix::allPrefixes[] =
{
{qMeasurePrefix::Quecto, "q",  1.0e-30, false },
{qMeasurePrefix::Ronto,  "r",  1.0e-27, false },
{qMeasurePrefix::Yocto,  "y",  1.0e-24, false },
{qMeasurePrefix::Zepto,  "z",  1.0e-21, false },
{qMeasurePrefix::Atto,   "a",  1.0e-18, false },
{qMeasurePrefix::Femto,  "f",  1.0e-15, false },
{qMeasurePrefix::Pico,   "p",  1.0e-12, false },
{qMeasurePrefix::Nano,   "n",  1.0e-9,  false },
{qMeasurePrefix::Micro,  "μ",  1.0e-6,  false },
{qMeasurePrefix::Micro,  "u",  1.0e-6,  true  },
{qMeasurePrefix::Milli,  "m",  0.001,   false },
{qMeasurePrefix::Centi,  "c",  0.01,    false },
{qMeasurePrefix::Deci,   "d",  0.1,     false },
{qMeasurePrefix::None,   "",   1.0,     false },
{qMeasurePrefix::Deca,   "da", 10,      false },
{qMeasurePrefix::Hecto,  "h",  100,     false },
{qMeasurePrefix::Kilo,   "k",  1000,    false },
{qMeasurePrefix::Mega,   "M",  1.0e6,   false },
{qMeasurePrefix::Giga,   "G",  1.0e9,   false },
{qMeasurePrefix::Tera,   "T",  1.0e12,  false },
{qMeasurePrefix::Peta,   "P",  1.0e15,  false },
{qMeasurePrefix::Exa,    "E",  1.0e18,  false },
{qMeasurePrefix::Zetta,  "Z",  1.0e21,  false },
{qMeasurePrefix::Yotta,  "Y",  1.0e24,  false },
{qMeasurePrefix::Ronna,  "R",  1.0e27,  false },
{qMeasurePrefix::Quetta, "Q",  1.0e30,  false },
};

qMeasurePrefix::qMeasurePrefix(Metric flags) : m_prefixes()
{
    for(int i = 0 ; i < sizeof(allPrefixes) / sizeof(allPrefixes[0]); i++)
    {
        if (allPrefixes[i].flag & flags) {
            m_prefixes[allPrefixes[i].symbol] = i;
        }
    }
}

QStringList qMeasurePrefix::getAvailablePrefixStrings() const
{
    QStringList result;
    for(const auto& str : m_prefixes.keys() ) {
        result.append(str);
    }
    return result;
}

void qMeasurePrefix::fixupPrefixString(QString &) const
{

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


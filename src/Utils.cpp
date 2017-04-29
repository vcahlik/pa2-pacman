#include <cmath>
#include "Utils.h"

namespace Utils
{
    const double decimalPart(const double value)
    {
        double temp;
        return std::modf(value, &temp);
    }
}
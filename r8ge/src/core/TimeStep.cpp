//
// Created by Vojta on 26.02.2024.
//

#include "TimeStep.h"

namespace r8ge {
    TimeStep::TimeStep(double time)
    {
        m_time = time;
    }

    double TimeStep::getSeconds() const
    {
        return m_time;
    }

    double TimeStep::getMilliseconds() const
    {
        return m_time * 1000;
    }
} // r8ge
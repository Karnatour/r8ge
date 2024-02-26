//
// Created by Vojta on 26.02.2024.
//

#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace r8ge
{
    class TimeStep
    {
    public:
        explicit TimeStep(double time = 0);
        [[nodiscard]] double getSeconds() const;

        [[nodiscard]] double getMilliseconds() const;

    private:
        double m_time = 0.0f;
    };
} // r8ge

#endif //TIMESTEP_H

#pragma once

#include <cmath>
#include <exception>
#include <stdint.h>

namespace DX
{
    class StepTimer
    {
    public:
        StepTimer() noexcept(false) :
            m_elapsedTicks(0),
            m_totalTicks(0),
            m_leftOverTicks(0),
            m_frameCount(0),
            m_framesPerSecond(0),
            m_framesThisSecond(0),
            m_qpcSecondCounter(0),
            m_isFixedTimeStep(false),
            m_targetElapsedTicks(TicksPerSecond / 60)
        {
            if (!QueryPerformanceFrequency(&m_qpcFrequency))
            {
                throw std::exception( "QueryPerformanceFrequency" );
            }

            if (!QueryPerformanceCounter(&m_qpcLastTime))
            {
                throw std::exception( "QueryPerformanceCounter" );
            }

            m_qpcMaxDelta = static_cast<uint64_t>(m_qpcFrequency.QuadPart / 10);
        }

        uint64_t GetElapsedTicks() const					{ return m_elapsedTicks; }
        double GetElapsedSeconds() const					{ return TicksToSeconds(m_elapsedTicks); }

        uint64_t GetTotalTicks() const						{ return m_totalTicks; }
        double GetTotalSeconds() const						{ return TicksToSeconds(m_totalTicks); }

        uint32_t GetFrameCount() const						{ return m_frameCount; }

        uint32_t GetFramesPerSecond() const					{ return m_framesPerSecond; }

        void SetFixedTimeStep(bool isFixedTimestep)			{ m_isFixedTimeStep = isFixedTimestep; }

        void SetTargetElapsedTicks(uint64_t targetElapsed)	{ m_targetElapsedTicks = targetElapsed; }
        void SetTargetElapsedSeconds(double targetElapsed)	{ m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

        static const uint64_t TicksPerSecond = 10000000;

        static double TicksToSeconds(uint64_t ticks)		{ return static_cast<double>(ticks) / TicksPerSecond; }
        static uint64_t SecondsToTicks(double seconds)		{ return static_cast<uint64_t>(seconds * TicksPerSecond); }

        void ResetElapsedTime()
        {
            if (!QueryPerformanceCounter(&m_qpcLastTime))
            {
                throw std::exception("QueryPerformanceCounter");
            }

            m_leftOverTicks = 0;
            m_framesPerSecond = 0;
            m_framesThisSecond = 0;
            m_qpcSecondCounter = 0;
        }

        template<typename TUpdate>
        void Tick(const TUpdate& update)
        {
            LARGE_INTEGER currentTime;

            if (!QueryPerformanceCounter(&currentTime))
            {
                throw std::exception( "QueryPerformanceCounter" );
            }

            uint64_t timeDelta = currentTime.QuadPart - m_qpcLastTime.QuadPart;

            m_qpcLastTime = currentTime;
            m_qpcSecondCounter += timeDelta;

            if (timeDelta > m_qpcMaxDelta)
            {
                timeDelta = m_qpcMaxDelta;
            }

            timeDelta *= TicksPerSecond;
            timeDelta /= m_qpcFrequency.QuadPart;

            uint32_t lastFrameCount = m_frameCount;

            if (m_isFixedTimeStep)
            {

                if (static_cast<uint64_t>(std::abs(static_cast<int64_t>(timeDelta - m_targetElapsedTicks))) < TicksPerSecond / 4000)
                {
                    timeDelta = m_targetElapsedTicks;
                }

                m_leftOverTicks += timeDelta;

                while (m_leftOverTicks >= m_targetElapsedTicks)
                {
                    m_elapsedTicks = m_targetElapsedTicks;
                    m_totalTicks += m_targetElapsedTicks;
                    m_leftOverTicks -= m_targetElapsedTicks;
                    m_frameCount++;

                    update();
                }
            }
            else
            {
                m_elapsedTicks = timeDelta;
                m_totalTicks += timeDelta;
                m_leftOverTicks = 0;
                m_frameCount++;

                update();
            }

            if (m_frameCount != lastFrameCount)
            {
                m_framesThisSecond++;
            }

            if (m_qpcSecondCounter >= static_cast<uint64_t>(m_qpcFrequency.QuadPart))
            {
                m_framesPerSecond = m_framesThisSecond;
                m_framesThisSecond = 0;
                m_qpcSecondCounter %= m_qpcFrequency.QuadPart;
            }
        }

    private:
        LARGE_INTEGER m_qpcFrequency;
        LARGE_INTEGER m_qpcLastTime;
        uint64_t m_qpcMaxDelta;

        uint64_t m_elapsedTicks;
        uint64_t m_totalTicks;
        uint64_t m_leftOverTicks;

        uint32_t m_frameCount;
        uint32_t m_framesPerSecond;
        uint32_t m_framesThisSecond;
        uint64_t m_qpcSecondCounter;

        bool m_isFixedTimeStep;
        uint64_t m_targetElapsedTicks;
    };
}

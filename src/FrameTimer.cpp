// clang-format off
#include "pch.h"
#include "FrameTimer.h"
#include "EventSystem.h"
// clang-format on

namespace Celestia
{

FrameTimer::FrameTimer(EventBus &eventBus) : eventBus(eventBus)
{
    setupEventSubscriptions();

    m_lastTime = SDL_GetTicks() / 1000.0f;
    m_deltaTime = 0.0f;
    m_simulationTime = 0.0f;
    m_simulationDeltaTime = 0.0f;
    m_simulationPaused = false;

    m_fps = 0.0f;
    m_stableFPS = 0.0f;
    m_timeAccumulator = 0.0f;
    m_frameCount = 0;
}

void FrameTimer::update()
{
    float currentTime = SDL_GetTicks() / 1000.0f;
    m_deltaTime = currentTime - m_lastTime;
    m_lastTime = currentTime;

    if (!m_simulationPaused)
    {
        m_simulationDeltaTime = m_deltaTime;
        m_simulationTime += m_simulationDeltaTime;
    }
    else
    {
        m_simulationDeltaTime = 0.0f;
    }

    // preventing it to devide with zero. So...if delta time is ever zero for some
    // reason
    if (m_deltaTime > 0.0f)
    {
        m_fps = 1.0f / m_deltaTime;
    }

    m_timeAccumulator += m_deltaTime;
    m_frameCount++;

    if (m_timeAccumulator >= 1.0f)
    {
        //  calculates the average framerate over a second. The current framerate
        //  can vary strongly if delta time is getting smaller
        m_stableFPS = m_frameCount / m_timeAccumulator;
        m_frameCount = 0;
        m_timeAccumulator = 0.0f;
    }

    // publish events from EventTimer here, because they are not part of any
    // SDL_EVENTS. SDL_EVENTS, so keyboard and mouse events
    eventBus.publish(FrameUpdateEvent(m_deltaTime, m_lastTime, m_simulationTime, m_simulationDeltaTime, m_stableFPS,
                                      m_simulationPaused));
}

void FrameTimer::setupEventSubscriptions()
{
    eventBus.subscribe<SimulationPausedChanged>(
        [this](const SimulationPausedChanged &ev) { m_simulationPaused = ev.paused; });
}

} // namespace Celestia

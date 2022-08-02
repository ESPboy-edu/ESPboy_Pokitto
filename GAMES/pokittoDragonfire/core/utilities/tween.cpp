#include "tween.h"

#include <cmath>
#include <algorithm>

#include "core//rendersystem.h"

Tween::Tween(float duration, bool repeats) :
    m_duration(uint32_t(duration*1000)),
    m_repeats(repeats)
{
    reset();
}

Tween::Tween(Tween::Easing c, float duration, bool repeats) :
    m_duration(uint32_t(duration*1000)),
    m_repeats(repeats),
    m_curve(c)
{
    reset();
}

Tween::Tween(Tween::Easing c_out, Tween::Easing c_back, float duration, bool repeat) :
    m_duration(uint32_t(duration*1000)),
    m_out_and_back(true),
    m_repeats(repeat),
    m_curve(c_out),
    m_curve_back(c_back)
{
    reset();
}

void Tween::reset(int32_t delay)
{
    m_start_time = RenderSystem::getTimeMs();
    m_delay = delay;
}

void Tween::end()
{
    m_start_time = RenderSystem::getTimeMs() - m_duration - m_delay;
}

void Tween::setDelay(float duration)
{
    m_delay = uint32_t(duration * 1000);
}

void Tween::setRepeat(bool repeats)
{
    m_repeats = repeats;
}

float Tween::getInterpolation(float start, float end) const
{
    int delta = int(RenderSystem::getTimeMs()) - int(m_start_time);
    if (delta < int(m_delay)) return start;
    float t = std::min(std::max(float(delta - m_delay)/float(m_duration), 0.0f), 1.0f);
    if (m_repeats) {
        delta = delta % int(m_duration + m_delay);
        t = std::max(0.0f, float(delta - int(m_delay))/float(m_duration));
    }

    if (!m_out_and_back) {
        t = map(t, m_curve);
    } else {
        if (t < 0.5f) {
            t = map(t * 2.0f, m_curve);
        } else {
            t = map((1.0f - t) * 2.0f, m_curve_back);
        }
    }

    return t * end + (1 - t) * start;
}

float Tween::getInterpolation(float start, float apex, float end, float threshold) const
{
    int delta = int(RenderSystem::getTimeMs()) - int(m_start_time);
    float t = std::min(std::max(float(delta - m_delay)/float(m_duration), 0.0f), 1.0f);
    if (m_repeats) {
        delta = delta % int(m_duration + m_delay);
        t = std::max(0.0f, float(delta - int(m_delay))/float(m_duration));
    }

    if (t < threshold) {
        t = map(t / threshold, m_curve);
        return t * apex + (1 - t) * start;
    } else {
        t = map((1.0f - t) / (1 - threshold), m_curve_back);
        return t * apex + (1 - t) * end;
    }

}

int Tween::getInterpolationInt(float start, float end) const
{
    return std::floor(getInterpolation(start, end) + 0.5f);
}

bool Tween::done(int for_at_least_ms) const
{
    if (m_repeats) return false;
    int delta = int(RenderSystem::getTimeMs()) - int(m_start_time) - for_at_least_ms;
    return (delta - m_delay) > m_duration;
}

bool Tween::started() const
{
    int delta = int(RenderSystem::getTimeMs()) - int(m_start_time);
    return delta >= m_delay;
}

void Tween::advance(int by_ms)
{
    m_start_time -= by_ms;
}

float Tween::map(float t, const Easing curve) const
{
    // remappings yoinked from this list:
    //   https://gist.github.com/gre/1650294
    switch (curve) {
    case Easing::OutQuad:
        return t * (2 - t);
    case Easing::InQuad:
        return t * t;
    case Easing::InOutQuad:
        return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
    default:
        return t;
    }
}



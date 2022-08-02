#ifndef TWEEN_H
#define TWEEN_H

#include <cstdint>

class Tween
{
public:
    enum Easing {
        Linear,
        OutQuad,
        InQuad,
        InOutQuad
    };

    Tween(float duration, bool repeat = false);

    Tween(Easing c, float duration, bool repeat = false);

    Tween(Easing c_out, Easing c_back, float duration, bool repeat = false);

    void reset(int32_t delay = 0);

    void end();

    void setDelay(float duration);

    void setRepeat(bool repeats);

    float getInterpolation(float start, float end) const;

    float getInterpolation(float start, float apex, float end, float threshold = 0.5f) const;

    int getInterpolationInt(float start, float end) const;

    bool done(int for_at_least_ms = 0) const;

    bool started() const;

    void advance(int by_ms);

    int32_t length() const { return m_duration + m_delay; }

private:
    int32_t m_start_time;

    int32_t m_duration;

    int32_t m_delay = 0;

    bool m_repeats = false;

    bool m_out_and_back = false;

    Easing m_curve = Easing::Linear;
    Easing m_curve_back = Easing::Linear;

    float map(float t, const Easing curve) const;
};

#endif // TWEEN_H

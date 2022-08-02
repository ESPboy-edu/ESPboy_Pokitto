#ifndef __CONTROLS
#define __CONTROLS

#include <cstdint>

class Controls;
class Button {
    uint16_t downCount = 0;
    uint16_t lastDownCount = 0;

    friend Controls;
public:
    void update(bool held) { lastDownCount = downCount; downCount = held ? downCount + 1 : 0; }
    bool pressed() const { return downCount == 1; }
    bool held() const { return downCount > 0; }
    bool justReleased() const { return downCount == 0 && lastDownCount != 0;}

    uint16_t holdCount() const { return downCount; }
    bool releasedWithin(int count) const { return lastDownCount > 0 && lastDownCount < count && downCount == 0; }
    bool downEvery(int initial, int thereafter) const {
        return initial == downCount || (downCount > initial && (downCount - initial) % thereafter == 0);
    }
};

struct ControlStatus {
  float x = 0.0f, y = 0.0f;
  Button up, down, left, right, a, b, c;
};

class Controls {
    ControlStatus m_stats;

    static Controls s_controls;

public:
    static void update();

    static const ControlStatus getStatus(bool normalize_dir = false);
};

#endif

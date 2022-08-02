#ifndef FPSHELPER_H
#define FPSHELPER_H

class FPSHelper {
    float m_fps_list[10] = { 0 };
    float lastTime = 0;

    int active_idx = 0;
public:
    FPSHelper() { update(); }

    void reset();
    void update();
    void draw(int x, int y, int color) const;
    void draw(int x, int y, int color_bg, int color_fg) const;
};

#endif // FPSHELPER_H

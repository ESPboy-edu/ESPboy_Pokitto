#include "fpshelper.h"

#include <string>

#include "core/rendersystem.h"

void FPSHelper::reset()
{
    lastTime = RenderSystem::getTimeMs();
}

void FPSHelper::update()
{
    if (RenderSystem::getTimeMs() == lastTime) return;
    m_fps_list[active_idx] = 1000.0f/float(RenderSystem::getTimeMs() - lastTime);
    lastTime = RenderSystem::getTimeMs();
    active_idx = (active_idx + 1) % 10;
}

void FPSHelper::draw(int x, int y, int color) const
{
    float avg = 0.0f;
    for(auto t : m_fps_list) {
        avg += t / 10;
    }
    char fpses[10];
    std::sprintf(fpses, "fps:%d", int(avg));
    RenderSystem::print(x, y, fpses, color);
}

void FPSHelper::draw(int x, int y, int color_bg, int color_fg) const
{
    float avg = 0.0f;
    for(auto t : m_fps_list) {
        avg += t / 10;
    }
    char fpses[10];
    std::sprintf(fpses, "fps:%d", int(avg));
    RenderSystem::print(x, y + 1, fpses, color_bg);
    RenderSystem::print(x, y, fpses, color_fg);
}

#ifndef _CTRLS

#define _CTRLS

#include "controls.h"

#include <cmath>

Controls Controls::s_controls;

#include <Pokitto.h>
#include <limits>

void Controls::update() {
    Pokitto::Buttons::pollButtons();
    s_controls.m_stats.up.update(Pokitto::Buttons::upBtn());
    s_controls.m_stats.down.update(Pokitto::Buttons::downBtn());
    s_controls.m_stats.left.update(Pokitto::Buttons::leftBtn());
    s_controls.m_stats.right.update(Pokitto::Buttons::rightBtn());

    s_controls.m_stats.y = 0;
    if (s_controls.m_stats.up.downCount > 0 && s_controls.m_stats.down.downCount > 0) { // NOTE: dpad on pokitto can get stuck with both buttons down after quickly alternating
      s_controls.m_stats.y = s_controls.m_stats.up.downCount < s_controls.m_stats.down.downCount ? -1 : 1;
    } else if (s_controls.m_stats.up.downCount > 0) {
      s_controls.m_stats.y = -1;
    } else if (s_controls.m_stats.down.downCount > 0) {
      s_controls.m_stats.y = 1;
    }

    s_controls.m_stats.x = 0;
    if (s_controls.m_stats.right.downCount > 0 && s_controls.m_stats.left.downCount > 0) {
      s_controls.m_stats.x = s_controls.m_stats.right.downCount < s_controls.m_stats.left.downCount ? 1 : -1;
    } else if (s_controls.m_stats.right.downCount > 0) {
      s_controls.m_stats.x = 1;
    } else if (s_controls.m_stats.left.downCount > 0) {
      s_controls.m_stats.x = -1;
    }

    s_controls.m_stats.a.update(Pokitto::Buttons::aBtn());
    s_controls.m_stats.b.update(Pokitto::Buttons::bBtn());
    s_controls.m_stats.c.update(Pokitto::Buttons::cBtn());
}

const ControlStatus Controls::getStatus(bool normalize_dir)
{
    ControlStatus out = s_controls.m_stats;

    if (normalize_dir && fabs(out.x) > std::numeric_limits<float>::epsilon() && fabs(out.y) > std::numeric_limits<float>::epsilon()) {
        out.x *= 0.7071f;
        out.y *= 0.7071f;
    }

    return out;
}


#endif
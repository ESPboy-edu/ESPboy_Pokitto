#ifndef _RECT
#define _RECT

#include "vec.h"

#ifdef DEBUGS
#include <iostream>
#endif

struct Bounds {
    int8_t w, h;
    Bounds() = default;
    constexpr Bounds(int sz, int sh) : w(sz), h(sh) {}
};

class Rect {
  float m_l, m_t, m_r, m_b, m_w, m_h;

public:
  Rect() = default;
  constexpr Rect(float x, float y, float w, float h) : m_l(x), m_t(y), m_r(x+w), m_b(y+h), m_w(w), m_h(h) {}
  Rect(float x, float y, const Bounds &b) : Rect(x - b.w/2, y - b.h/2, b.w, b.h) {}

  void grow(float w, float h);

  float left() const { return m_l; }
  float right() const { return m_r; }
  float top() const { return m_t; }
  float bottom() const { return m_b; }

  float centerX() const { return (m_l + m_r) * 0.5f; }
  float centerY() const { return (m_t + m_b) * 0.5f; }

  float width() const { return m_w; }
  float height() const { return m_h; }

  void setCenter(float x, float y);
  void shift(float x, float y);

  bool overlaps(const Rect &other) const;
  bool contains(const Vec2f &p) const;
  bool contains(float x, float y) const;

  static bool overlaps(const Rect &r1, const Rect &r2);

#ifdef DEBUGS
  void debugShow() {
      std::cout << m_l << " " << m_r << " " << m_t << " " << m_b << std::endl;
  }
#endif
};

#endif

#include "rect.h"

void Rect::grow(float w, float h)
{
    float x = centerX();
    float y = centerY();
    m_w += w;
    m_h += h;
    setCenter(x, y);
}

void Rect::setCenter(float x, float y) {
  m_l = x - m_w/2.0f;
  m_r = x + m_w/2.0f;
  m_t = y - m_h/2.0f;
  m_b = y + m_h/2.0f;
}

void Rect::shift(float x, float y)
{
    m_r += x;
    m_l += x;
    m_t += y;
    m_b += y;
}

bool Rect::overlaps(const Rect &other) const
{
    return Rect::overlaps(*this, other);
}

bool Rect::contains(const Vec2f &p) const
{
    return contains(p.x(), p.y());
}

bool Rect::contains(float x, float y) const
{
    return x >= m_l && x <= m_r && y >= m_t && y <= m_b;
}

bool Rect::overlaps(const Rect &r1, const Rect &r2) {
  return r1.m_l < r2.m_r
      && r2.m_l < r1.m_r
      && r1.m_t < r2.m_b
      && r2.m_t < r1.m_b;
}


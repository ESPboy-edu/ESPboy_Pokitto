#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <stdint.h>

class Vec2f
{
    float m_x, m_y;

public:
    Vec2f() = default;
    constexpr Vec2f(float x, float y) : m_x(x), m_y(y) {}
    constexpr Vec2f(const Vec2f &other) : m_x(other.m_x), m_y(other.m_y) {}

    float x() const { return m_x; }
    float y() const { return m_y; }
    float length() const { return std::sqrt(m_x*m_x+m_y*m_y); }

    void set(float x, float y) { m_x = x; m_y = y; }
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    Vec2f rot90() const { return Vec2f(m_y, -m_x); }

    Vec2f abs() const { return Vec2f(std::fabs(m_x), std::fabs(m_y)); }

    void rotBy(float angle, bool normalize = true) {
        float l = 1.0f;
        if (!normalize) l = length();
        if (l == 0) return;
        float a = std::atan2(m_y, m_x);
        a += angle / 180.0f * 3.1415926f;
        m_x = std::cos(a) * l;
        m_y = std::sin(a) * l;
    }

    float dot(const Vec2f &other) { return m_x * other.m_x + m_y * other.m_y; }

    Vec2f operator-(const Vec2f &other) const {
        return Vec2f(m_x - other.m_x, m_y - other.m_y);
    }

    Vec2f operator+(const Vec2f &other) const {
        return Vec2f(m_x + other.m_x, m_y + other.m_y);
    }

    Vec2f& operator+=(const Vec2f &other) {
        m_x += other.m_x;
        m_y += other.m_y;
//        m_init = false;
        return *this;
    }

    constexpr Vec2f operator*(float val) const {
        return Vec2f(m_x * val, m_y * val);
    }

    constexpr Vec2f operator*(const Vec2f &other) const {
        return Vec2f(m_x * other.m_x, m_y * other.m_y);
    }

    Vec2f& operator*=(float val) {
        m_x *= val;
        m_y *= val;
//        m_length *= val;
        return *this;
    }

    Vec2f operator/(float val) const {
        return Vec2f(m_x / val, m_y / val);
    }

    Vec2f& operator/=(float val) {
        m_x /= val;
        m_y /= val;
//        m_length /= val;
        return *this;
    }

    int getRotationFrame(int frame_count) const {
        float anglePerFrame = 180.0f / frame_count;
        float angle = std::atan2(m_y, std::abs(m_x)) * 180.0f / 3.1415926f;
        angle = angle + 90.0f + anglePerFrame / 2.0f; // shift atan2 to [0,180]
        return uint8_t(angle / 180.0f * frame_count);
    }
};


class Vec2i
{
    int16_t m_x, m_y;

public:
    Vec2i() = default;
    constexpr Vec2i(float x, float y) : m_x(x), m_y(y) {}
    constexpr Vec2i(const Vec2i &other) : m_x(other.m_x), m_y(other.m_y) {}

    int x() const { return m_x; }
    int y() const { return m_y; }
    float length() const { return std::sqrt(m_x*m_x+m_y*m_y); }

    void set(uint16_t x, uint16_t y) { m_x = x; m_y = y; }
    void setX(uint16_t x) { m_x = x; }
    void setY(uint16_t y) { m_y = y; }

    Vec2i rot90() const { return Vec2i(m_y, -m_x); }

    float dot(const Vec2i &other) { return m_x * other.m_x + m_y * other.m_y; }

    Vec2i operator-(const Vec2i &other) const {
        return Vec2i(m_x - other.m_x, m_y - other.m_y);
    }

    Vec2i operator+(const Vec2i &other) const {
        return Vec2i(m_x + other.m_x, m_y + other.m_y);
    }

    Vec2i& operator+=(const Vec2i &other) {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }

    constexpr Vec2i operator*(float val) const {
        return Vec2i(m_x * val, m_y * val);
    }

    operator Vec2f() const {
        return Vec2f(m_x, m_y);
    }

    Vec2i& operator*=(float val) {
        m_x *= val;
        m_y *= val;
        return *this;
    }

    Vec2i operator/(float val) const {
        return Vec2i(float(m_x) / val, float(m_y) / val);
    }

    Vec2i& operator/=(float val) {
        m_x = float(m_x)/val;
        m_y = float(m_y)/val;
        return *this;
    }
};
#endif // VEC_H

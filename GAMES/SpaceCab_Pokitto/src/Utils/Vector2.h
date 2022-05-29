#pragma once


class Vector2 {
	
  public:

    float x = 0;
    float y = 0;

  public:

    constexpr Vector2(void) = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

};

inline constexpr Vector2 operator+(Vector2 left, Vector2 right) {
    return Vector2(left.x + right.x, left.y + right.y);
}

inline constexpr Vector2 operator-(Vector2 left, Vector2 right) {
    return Vector2(left.x - right.x, left.y - right.y);
}
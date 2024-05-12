#pragma once

#include <cstdint>

namespace TAS {

    using LineFiller = void (*)(std::uint8_t *line, std::uint32_t y, bool skip);

//void pixelCopy(uint8_t* dest, const uint8_t *src, uint32_t count, uint32_t recolor);
//void pixelCopyMirror(uint8_t* dest, const uint8_t *src, uint32_t count, uint32_t recolor);

//void pixelCopySolid4BPP(uint8_t *line, const uint8_t *src, uint32_t w, uint32_t sx);
//void pixelCopySolid(uint8_t* dest, const uint8_t *src, uint32_t count, uint32_t recolor);

void flushLine(const uint16_t *palette, const uint8_t *line);
void flushLine2X(const uint16_t *palette, const uint8_t *line);
void lcdRefreshTASMode(const uint16_t* palette);

    void BGTileFiller(std::uint8_t *line, std::uint32_t y, bool skip);
    void SpriteFiller(std::uint8_t *line, std::uint32_t y, bool skip);
    void ColorFiller(std::uint8_t* line, std::uint32_t y, bool skip);
    void DitherFiller(std::uint8_t* line, std::uint32_t y, bool skip);
    inline void NOPFiller(std::uint8_t* line, std::uint32_t y, bool skip){};
}

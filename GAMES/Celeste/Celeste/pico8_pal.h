
#include <Arduino.h>
#include <stdint.h>

const PROGMEM uint8_t pico8[] = {
	3,5,0,0, // height

    // font data
    3,0x3F, 0x21, 0x3F, // 0
    3,0x12, 0x08, 0x12, // 1
    3,0x0A, 0x10, 0x0A, // 2
    3,0x0E, 0x1C, 0x0E, // 3
    3,0x0C, 0x1E, 0x0C, // 4
    3,0x14, 0x1A, 0x14, // 5
    3,0x16, 0x1F, 0x16, // 6
    3,0x1E, 0x13, 0x1E, // 7
    3,0x1E, 0x1B, 0x1E, // 8
    3,0x1E, 0x1F, 0x1E, // 9
    3,0x3F, 0x21, 0x3F, // 10
    3,0x3A, 0x2F, 0x3A, // 11
    3,0x17, 0x3D, 0x17, // 12
    3,0x3F, 0x21, 0x3F, // 13
    3,0x18, 0x1F, 0x02, // 14
    3,0x04, 0x0A, 0x04, // 15
    3,0x1F, 0x0E, 0x04, // 16
    3,0x04, 0x0E, 0x1F, // 17
    3,0x0A, 0x1F, 0x0A, // 18
    3,0x0E, 0x0E, 0x1F, // 19
    3,0x04, 0x11, 0x0E, // 20
    3,0x2E, 0x25, 0x2E, // 21
    3,0x2F, 0x2A, 0x2E, // 22
    3,0x26, 0x29, 0x29, // 23
    3,0x02, 0x1F, 0x02, // 24
    3,0x08, 0x1F, 0x08, // 25
    3,0x15, 0x0E, 0x04, // 26
    3,0x04, 0x0E, 0x15, // 27
    3,0x0E, 0x15, 0x15, // 28
    3,0x1B, 0x15, 0x1B, // 29
    3,0x04, 0x06, 0x04, // 30
    3,0x04, 0x0C, 0x04, // 31
    3,0x00, 0x00, 0x00, // 32
    3,0x00, 0x17, 0x00, // 33
    3,0x03, 0x00, 0x03, // 34
    3,0x1F, 0x0A, 0x1F, // 35
    3,0x0B, 0x1F, 0x0D, // 36
    3,0x19, 0x04, 0x13, // 37
    3,0x1F, 0x17, 0x18, // 38
    3,0x00, 0x03, 0x00, // 39
    3,0x00, 0x0E, 0x11, // 40
    3,0x11, 0x0E, 0x00, // 41
    3,0x15, 0x0E, 0x15, // 42
    3,0x04, 0x0E, 0x04, // 43
    3,0x00, 0x10, 0x08, // 44
    3,0x04, 0x04, 0x04, // 45
    3,0x00, 0x10, 0x00, // 46
    3,0x10, 0x0E, 0x01, // 47
    3,0x1F, 0x11, 0x1F, // 48
    3,0x11, 0x1F, 0x10, // 49
    3,0x1D, 0x15, 0x17, // 50
    3,0x11, 0x15, 0x1F, // 51
    3,0x07, 0x04, 0x1F, // 52
    3,0x17, 0x15, 0x1D, // 53
    3,0x1F, 0x14, 0x1C, // 54
    3,0x01, 0x01, 0x1F, // 55
    3,0x1F, 0x15, 0x1F, // 56
    3,0x07, 0x05, 0x1F, // 57
    3,0x00, 0x0A, 0x00, // 58
    3,0x10, 0x0A, 0x00, // 59
    3,0x04, 0x0A, 0x11, // 60
    3,0x0A, 0x0A, 0x0A, // 61
    3,0x11, 0x0A, 0x04, // 62
    3,0x01, 0x15, 0x07, // 63
    3,0x0E, 0x11, 0x16, // 64
    3,0x1F, 0x05, 0x1F, // 65
    3,0x1F, 0x15, 0x1B, // 66
    3,0x0E, 0x11, 0x11, // 67
    3,0x1F, 0x11, 0x1E, // 68
    3,0x1F, 0x15, 0x11, // 69
    3,0x1F, 0x05, 0x01, // 70
    3,0x1E, 0x11, 0x19, // 71
    3,0x1F, 0x04, 0x1F, // 72
    3,0x11, 0x1F, 0x11, // 73
    3,0x11, 0x1F, 0x01, // 74
    3,0x1F, 0x04, 0x1B, // 75
    3,0x1F, 0x10, 0x10, // 76
    3,0x1F, 0x03, 0x1F, // 77
    3,0x1F, 0x01, 0x1E, // 78
    3,0x1E, 0x11, 0x0F, // 79
    3,0x1F, 0x05, 0x07, // 80
    3,0x0E, 0x19, 0x16, // 81
    3,0x1F, 0x05, 0x1B, // 82
    3,0x16, 0x15, 0x0D, // 83
    3,0x01, 0x1F, 0x01, // 84
    3,0x0F, 0x10, 0x1F, // 85
    3,0x0F, 0x18, 0x0F, // 86
    3,0x1F, 0x18, 0x1F, // 87
    3,0x1B, 0x04, 0x1B, // 88
    3,0x17, 0x14, 0x1F, // 89
    3,0x19, 0x15, 0x13, // 90
    3,0x00, 0x1F, 0x11, // 91
    3,0x01, 0x0E, 0x10, // 92
    3,0x11, 0x1F, 0x00, // 93
    3,0x02, 0x01, 0x02, // 94
    3,0x10, 0x10, 0x10, // 95
    3,0x00, 0x01, 0x02, // 96
    3,0x1E, 0x0A, 0x1E, // 97
    3,0x1E, 0x16, 0x18, // 98
    3,0x1E, 0x12, 0x12, // 99
    3,0x1E, 0x12, 0x0C, // 100
    3,0x1E, 0x16, 0x12, // 101
    3,0x1E, 0x06, 0x02, // 102
    3,0x1E, 0x12, 0x1A, // 103
    3,0x1E, 0x08, 0x1E, // 104
    3,0x12, 0x1E, 0x12, // 105
    3,0x12, 0x1E, 0x02, // 106
    3,0x1E, 0x04, 0x1A, // 107
    3,0x1E, 0x10, 0x10, // 108
    3,0x1E, 0x06, 0x1E, // 109
    3,0x1E, 0x02, 0x1C, // 110
    3,0x1C, 0x12, 0x0E, // 111
    3,0x1E, 0x0A, 0x0E, // 112
    3,0x04, 0x1A, 0x14, // 113
    3,0x1E, 0x0A, 0x16, // 114
    3,0x14, 0x12, 0x0A, // 115
    3,0x02, 0x1E, 0x02, // 116
    3,0x0E, 0x10, 0x1E, // 117
    3,0x0E, 0x18, 0x0E, // 118
    3,0x1E, 0x18, 0x1E, // 119
    3,0x1A, 0x0C, 0x1A, // 120
    3,0x16, 0x14, 0x1E, // 121
    3,0x1A, 0x12, 0x16, // 122
    3,0x04, 0x0E, 0x11, // 123
    3,0x00, 0x1F, 0x00, // 124
    3,0x11, 0x1F, 0x04, // 125
    3,0x0C, 0x04, 0x06, // 126
    3,0x0E, 0x09, 0x0E // 127

};

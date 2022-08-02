#ifndef BABYFSM_H
#define BABYFSM_H

#include <cstdint>

const uint8_t maxStates = 10;

class FSM {
    void (*updates[maxStates])(FSM&);
    void (*draws[maxStates])();
    void (*gos[maxStates])();

    uint8_t m_current;

    bool m_initialized = false;

public:
    FSM() {
        instance = this;
    }

    FSM &add(uint8_t s, void (*upd)(FSM&) = nullptr, void (*drw)() = nullptr, void (*ongo)() = nullptr) {
        updates[s] = upd;
        draws[s] = drw;
        gos[s] = ongo;

        if (!m_initialized) {
            go(s);
            m_initialized = true;
        }
        return *this;
    }

    void go(uint8_t s) {
        if (s == m_current) {
            return;
        }
        m_current = s;
        if (gos[m_current] != nullptr) {
            gos[m_current]();
        }
    }

    void update() {
        if (updates[m_current] != nullptr) {
            updates[m_current](*this);
        }
    }

    void draw() {
        if (draws[m_current] != nullptr) {
            draws[m_current]();
        }
    }

    static FSM * instance;

    bool is(uint8_t mode) { return m_current == mode; }
};

#endif // BABYFSM_H

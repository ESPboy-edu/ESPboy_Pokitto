#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <cstdint>
#include <algorithm>
#include <functional>

template <class Obj, int Count>
class ObjectPool
{
    Obj m_objects[Count];

    uint8_t m_activeCount;

public:

    Obj * activateNext();

    void deactivate(Obj*);

    void deactivate(uint8_t);

    void clear();

    void iterate(std::function<bool(Obj*)> func);

    Obj * objects() { return m_objects; }

    int objectCount() const { return m_activeCount; }
};

template <class Obj, int Count>
class SimplePool
{
    Obj m_objects[Count];

    bool m_active[Count] = { false };

public:

    Obj * activateNext();

    void deactivate(Obj*);

    void deactivate(uint8_t);

    void clear();

    void iterate(std::function<bool(Obj*)> func);

    Obj * objects() { return m_objects; }

    int objectCount() const {
        int ct = 0;
        for (int i = 0; i < Count; ++i) {
            if (m_active[i]) ++ct;
        }
        return ct;
    }
};

template<class Obj, int Count>
Obj *ObjectPool<Obj,Count>::activateNext()
{
    if (m_activeCount == Count) {
        return nullptr;
    }
    m_activeCount++;
    return m_objects + m_activeCount - 1;
}

template<class Obj, int Count>
void ObjectPool<Obj,Count>::deactivate(Obj * target)
{
    if (m_activeCount == 0) {
        return;
    }
    int choice = -1;
    for(int i = Count - 1; i != -1; --i) {
        if (target == (m_objects + i)) {
            choice = i;
            break;
        }
    }
    if (choice >= 0) {
        deactivate(choice);
    }
}

template<class Obj, int Count>
void ObjectPool<Obj,Count>::deactivate(uint8_t idx)
{
    std::swap(m_objects[idx], m_objects[m_activeCount - 1]);
    --m_activeCount;
}

template<class Obj, int Count>
void ObjectPool<Obj,Count>::clear()
{
    m_activeCount = 0;
}

template<class Obj, int Count>
void ObjectPool<Obj, Count>::iterate(std::function<bool (Obj*)> func)
{
    for(Obj * i = m_objects + m_activeCount-1; i >= m_objects; --i) {
        if (func(i)) {
            deactivate(i);
        }
    }
}

template<class Obj, int Count>
Obj *SimplePool<Obj,Count>::activateNext()
{
    for (int i = 0; i < Count; ++i) {
        if (!m_active[i]) {
            m_active[i] = true;
            return m_objects + i;
        }
    }
}

template<class Obj, int Count>
void SimplePool<Obj,Count>::deactivate(Obj * obj)
{
    for (int i = 0; i < Count; ++i) {
        if (m_active[i] && m_objects[i] == obj) {
            m_active[i] = false;
            return;
        }
    }
}

template<class Obj, int Count>
void SimplePool<Obj,Count>::deactivate(uint8_t idx)
{
    if (idx < Count) m_active[idx] = false;
}

template<class Obj, int Count>
void SimplePool<Obj,Count>::clear()
{
    for (int i = 0; i < Count; ++i) {
        m_active[i] = false;
    }
}

template<class Obj, int Count>
void SimplePool<Obj,Count>::iterate(std::function<bool (Obj *)> func)
{
    for (int i = 0; i < Count; ++i) {
        if (m_active[i]) {
            m_active[i] = func(m_objects + i);
        }
    }
}

#endif // OBJECTPOOL_H

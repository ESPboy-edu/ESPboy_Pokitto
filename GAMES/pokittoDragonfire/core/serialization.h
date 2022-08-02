#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Pokitto.h"
//#include <File>

namespace Serialization {

    template<typename S>
    static bool tryStore(const char * fname, const S * data) {
  /*      File file;
        if (!file.openRW(fname, true, false)) {
            return false;
        }
        file.write(data, sizeof(S));
        return true;*/
        return false;
    }

    template<typename S>
    static bool tryGet(const char * fname, S * data) {
    /*    File file;
        if (!file.openRO(fname)) {
            return false;
        }
        file.read(data, sizeof(S));
        return true;*/
    return false;
    }
};

#endif // SERIALIZATION_H

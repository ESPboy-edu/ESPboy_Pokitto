#pragma once

namespace Audio {

    using u64 = unsigned long long;
    using u32 = unsigned int;
    using s32 = signed int;
    using u16 = unsigned short;
    using s16 = signed short;
    using u8 = unsigned char;
    using s8 = signed char;
    using Source = void (*)(u8*, void*);

    inline constexpr u32 bufferCount = 2;

    extern "C" {
        inline volatile u32 audio_volume;
        inline volatile u32 audio_playHead;
        inline volatile u8 audio_state[bufferCount];
        inline u8 audio_buffer[512 * bufferCount];
    }

    struct Channel {
        Source source;
        void *data;
    };

    namespace internal {

        inline void *sinkInstance = nullptr;

    }

    inline Channel (*connect)(u32 channelNumber, void *data, Source source);

    inline u8 mix(u8 a, u8 b){
        s32 v = s32(a) + s32(b) - 127;
        if(v < 0) return 0;
        if(v > 0xFF) return 0xFF;
        return v;
    }

    template <typename Derived, u32 channelCount>
    class BaseSink {
    protected:
        using Base = BaseSink<Derived, channelCount>;

        Channel channels[channelCount];
        u8 wasInit = false;
        void (*nextHook)(bool);

        BaseSink(){
            if(Audio::internal::sinkInstance)
                return;

            Audio::internal::sinkInstance = this;

            Audio::connect =
                +[](u32 channelNumber, void *data, Source source) {
                     auto self = reinterpret_cast<Derived*>(Audio::internal::sinkInstance);
                     return self->connect(channelNumber, data, source);
                 };

            nextHook = Pokitto::Core::updateHook;
            Pokitto::Core::updateHook =
                +[](bool isFrame){
                     auto self = reinterpret_cast<Derived*>(Audio::internal::sinkInstance);
                     self->update();
                     self->nextHook(isFrame);
                 };
        }

        Channel connect(u32 channelNumber, void *data, Source source){
            static_cast<Derived*>(this)->init();
            if(channelNumber >= channelCount)
                channelNumber = channelCount-1;
            auto prev = channels[channelNumber];
            channels[channelNumber].source = source;
            channels[channelNumber].data = data;
            return prev;
        }        

        void update(){
            reinterpret_cast<Derived*>(this)->init();
            for(u32 i = 0; i < bufferCount; ++i){
                if(audio_state[i])
                    continue;
                u8 *buffer = audio_buffer + i * 512;
                for(u32 c = 0; c < channelCount; ++c){
                    auto source = channels[c].source;
                    if(source){
                        source(buffer, channels[c].data);
                    }
                }
                audio_state[i] = 1;
            }
        }
    };
}


//#include "PokittoSimSink.hpp"
#include "SilenceSource.hpp"
#include "PokittoHWSink.hpp"
//#include "RAWFileSource.hpp"
#include "ByteBeatSource.hpp"
#include "SFX8Source.hpp"
#include "SynthSource.hpp"
#include "SimpleTune.hpp"

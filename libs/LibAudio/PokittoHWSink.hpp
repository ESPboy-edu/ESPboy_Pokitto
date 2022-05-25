#pragma once
#include <LittleFS.h>
#include <sigma_delta.h>


namespace Audio {

    inline void setVolume(u32 v){
    }

    inline void mix(void *dst, const void* src, std::size_t count) {
        u8 *buffer = static_cast<u8*>(dst);
        const u8 *tmp = static_cast<const u8*>(src);
        for(u32 i=0; i<count; ++i){
            s32 v = s32(buffer[i]) + s32(tmp[i]) - 128;
            if(v < 0) v = 0;
            else if(v > 0xFF) v = 0xFF;
            buffer[i] = v;
        }
    }

    template <u32 channelCount, u32 sampleRate>
    class Sink : public BaseSink<Sink<channelCount, sampleRate>, channelCount> {
        void enableDAC() {  
          attachDAC();}
        
        void detachDAC(){
          noInterrupts();
          timer1_disable();
          sigmaDeltaDisable();
          interrupts();};
        
        void attachDAC(){
          noInterrupts();
          sigmaDeltaSetup(0, 48000);
          sigmaDeltaAttachPin(D3);
          sigmaDeltaEnable();
          timer1_attachInterrupt(IRQ);
          timer1_enable(TIM_DIV1, TIM_EDGE, TIM_LOOP);
          timer1_write(80000000 / sampleRate * 2);
          interrupts(); 
        };
        
        
    static void IRAM_ATTR IRQ(void){
            static u8 lastByte = 128;
            
            auto currentBuffer = audio_playHead >> 9;
            
            if(!audio_state[currentBuffer]){
              sigmaDeltaWrite(0, lastByte);
              return;
            }
            
            lastByte = audio_buffer[audio_playHead];
            audio_playHead++;

            auto nextBuffer = audio_playHead >> 9;

            if(currentBuffer != nextBuffer){
                audio_state[currentBuffer] = 0;
                if(nextBuffer == bufferCount)
                    audio_playHead = 0;
             }
            sigmaDeltaWrite(0, lastByte/* * audio_volume >> 8*/);// lastByte * audio_volume >> 8;
        }


    public:
        void init(){
            if(this->wasInit)
                return;
            this->wasInit = true;

            this->channels[0].source =
                +[](u8 *buffer, void *ptr){
                     memset(buffer, 128, 512);
                 };

            for(int i=1; i<channelCount; ++i){
                this->channels[i].source = nullptr;
            }

            for(int i=0; i<bufferCount; ++i){
                audio_state[i] = 0;
            }
            audio_playHead = 0;

            memset(audio_buffer, 128, 1024);
            enableDAC();
        }

        Sink() = default;
    };
}

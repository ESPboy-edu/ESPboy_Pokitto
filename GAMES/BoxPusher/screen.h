uint16_t alphaBlendRGB565(uint32_t fg, uint32_t bg, uint8_t alpha) {

    fg = (fg | fg << 16) & 0x07e0f81f;
    bg = (bg | bg << 16) & 0x07e0f81f;
    bg += (fg - bg) * alpha >> 5;
    bg &= 0x07e0f81f;
        return (uint16_t)(bg | bg >> 16);
}

void clearText(){
    for(int t=0; t<594; t++){
        guiBG[t]=0;
    }
}

void drawSprite(int x, int y, const uint8_t *imageData,const uint16_t *paletteData, bool hFlip, uint8_t bit){ 
    // if out of screen bounds, don't bother
    
    if(x<-32 || x>220) return;
    if(y<-32 || y>175) return;

    if(++spriteCount>NUMSPRITES-1)spriteCount=NUMSPRITES-1; // don't overflow the sprite max

    sprites[spriteCount].x = x;
    sprites[spriteCount].y = y;
    sprites[spriteCount].imageData = imageData;
    sprites[spriteCount].paletteData = paletteData;
    sprites[spriteCount].hFlip = hFlip;
    sprites[spriteCount].bit = bit;

    // make sure we know there are sprites on these lines
    int y2 = y+sprites[spriteCount].imageData[1];
    for(int t=y; t<y2; t++){
        if(t>=0 && t<176)
            spriteLine[t]=1;
    }
}




void spritesToLine(std::uint8_t* line, std::uint32_t y, bool skip){

    if(spriteLine[y]==0) return;   

    auto scanLine = &Pokitto::Display::palette[32]; // start 32 pixels in because of underflow
    
    int y2 = y;

    spriteLine[y]=0;
    if(spriteCount>=0){
        for(int32_t spriteIndex = 1; spriteIndex<=spriteCount; spriteIndex++){
            auto &sprite = sprites[spriteIndex];
            if((int)y >= sprite.y && (int)y < sprite.y + sprite.imageData[1]){
                if(sprite.x>-32 && sprite.x</*PROJ_LCDWIDTH*/255-64){
                    auto sl = &scanLine[sprite.x];
                    auto palette = sprite.paletteData;

                    if(sprite.bit==2){
                        uint32_t so = 2+((32>>2) * (y2-sprite.y));
                        if(sprite.hFlip){
                            auto si = &sprite.imageData[so+7];
                            auto pixel = *si;
                            #define midLoop2()\
                                if(pixel = *si&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si>>2&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si>>4&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si>>6&3) *sl = palette[pixel];\
                                si--; sl++;
                            midLoop2(); midLoop2(); midLoop2(); midLoop2(); midLoop2(); midLoop2(); midLoop2(); midLoop2(); 
                        }else{
                            auto si = &sprite.imageData[so];
                            auto pixel = *si;
                            #define midLoop21()\
                                if(pixel = *si>>6&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si>>4&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si>>2&3) *sl = palette[pixel];\
                                sl++;\
                                if(pixel = *si&3) *sl = palette[pixel];\
                                si++; sl++;
                            midLoop21(); midLoop21(); midLoop21(); midLoop21(); midLoop21(); midLoop21(); midLoop21(); midLoop21(); 
                        }
                    }

                    if(sprite.bit==4){
                        uint32_t so = 2+((32>>1) * (y2-sprite.y));
                        if(sprite.hFlip){
                            auto si = &sprite.imageData[so+31];
                            #define midLoop4()\
                                if(auto pixel = *si&15) *sl = palette[pixel];\
                                sl++;\
                                if(auto pixel = *si>>4) *sl = palette[pixel];\
                                si--; sl++;
                            midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); 
                            midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); midLoop4(); 
                        }else{
                            auto si = &sprite.imageData[so];
                            #define midLoop41()\
                                if(auto pixel = *si>>4) *sl = palette[pixel];\
                                sl++;\
                                if(auto pixel = *si&15) *sl = palette[pixel];\
                                si++; sl++;
                            midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); 
                            midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); midLoop41(); 
                        }
                    }

                    if(sprite.bit==8){
                        uint32_t so = 2+(32 * (y2-sprite.y));
                        if(sprite.hFlip){
                            auto si = &sprite.imageData[so+31];
                            #define midLoop8()\
                                if(auto pixel = *si) *sl = palette[pixel];\
                                si--; sl++;
                            midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); 
                            midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); 
                            midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); 
                            midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); midLoop8(); 
                        }else{
                            auto si = &sprite.imageData[so];
                            #define midLoop81()\
                                if(auto pixel = *si) *sl = palette[pixel];\
                                si++; sl++;
                            midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); 
                            midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); 
                            midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); 
                            midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); midLoop81(); 
                        }
                    }
                    
                } // if X
            } // if Y
        } // for spriteCount
    } // sprite count >1
    
}



inline void GUILine(std::uint8_t* line, std::uint32_t y, bool skip){
    uint8_t tl = y/8;
    if(guiLineHasText[tl]==0) return;

    int yVal = 2 + ((y&7)*4);
    if(guiLineHasText[tl]==1){
        uint32_t x = 0;
        uint32_t tileIndex = tl * 27;
        uint32_t lineOffset;
        uint32_t alpha = 16;
        uint32_t temp;
        auto &tileRef = guiFont[0];
        auto scanLine = &Pokitto::Display::palette[32]; // start 32 pixels in because of underflow
        for(int d=0; d<27; d++){
            lineOffset = yVal + guiBG[tileIndex++]*34;
            if(guiBG[tileIndex-1]){
                #define innerLoop()\
                    temp = tileRef[lineOffset]>>4;\
                    if(temp){ scanLine[x] = guiFont_pal[temp]; }\
                    x++;\
                    temp = tileRef[lineOffset++]&15;\
                    if(temp){ scanLine[x] = guiFont_pal[temp]; }\
                    x++;
    
                innerLoop();
                innerLoop();
                innerLoop();
                innerLoop();
            }else{
                x+=8;
            }
        }
    }else{
        uint32_t x = 0;
        uint32_t tileIndex = tl * 27;
        uint32_t lineOffset;
        uint32_t alpha = 16;
        uint32_t temp;
        auto &tileRef = guiFont[0];
        auto scanLine = &Pokitto::Display::palette[32]; // start 32 pixels in because of underflow
        for(int d=0; d<27; d++){
            lineOffset = yVal + guiBG[tileIndex++]*34;
            if(guiBG[tileIndex-1]){
                #define innerLoopT()\
                    temp = tileRef[lineOffset]>>4;\
                    if(temp==0){\
                        scanLine[x] = alphaBlendRGB565(0x07FF, scanLine[x], alpha);\
                    }else if(temp){\
                        scanLine[x] = guiFont_pal[temp];\
                    }\
                    x++;\
                    temp = tileRef[lineOffset++]&15;\
                    if(temp==0){\
                        scanLine[x] = alphaBlendRGB565(0x07FF, scanLine[x], alpha);\
                    }else if(temp){\
                        scanLine[x] = guiFont_pal[temp];\
                    }\
                    x++;
                
                innerLoopT();
                innerLoopT();
                innerLoopT();
                innerLoopT();
            }else{
                x+=8;
            }
        }
    }
}


inline void myBGFiller(std::uint8_t* line, std::uint32_t y, bool skip){
       if(y==0){
        for(uint32_t x=0; x<220; ++x){
            line[x]=x+32;
        }        
    }

    #define TILEWIDTH 32
    #define TILEHEIGHT 32

    // how far off screen should we render the map
    int x = -(xScroll%TILEWIDTH)+TILEWIDTH;
    // find current tile in the map
    int tileIndex = (xScroll/TILEWIDTH) + ((y+yScroll)/TILEHEIGHT) * levWidth;
    // Find first pixel in current line of the tile
    int jStart = 2+((y+yScroll)%TILEHEIGHT)*TILEWIDTH;

    auto lineP = &Pokitto::Display::palette[x];
    auto tilesP = &tiles[0];

    #define bgTileLine()\
        lineP = &Pokitto::Display::palette[x];\
        tilesP = &tiles[(curLevel[tileIndex++]*1024) + jStart];\
        x+=32;\
        memcpy(lineP, tilesP, 64);

/*
    #define bgHalfTileLine()\
        lineP = &Pokitto::Display::palette[x];\
        tilesP = &tiles[(curLevel[tileIndex++]*1024) + jStart];\
        memcpy(lineP, tilesP, 252*2);
*/
    bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine();
    bgTileLine(); bgTileLine(); bgTileLine();
    //bgHalfTileLine();

    //GUILine(line, y, 0);
    //spritesToLine(y);
    //flushLine(Pokitto::Display::palette, line);
    
}

//int z_line = 0;


/*
inline void myBGFiller2(std::uint8_t* line, std::uint32_t y, bool skip){

    if(y==0){
        for(uint32_t x=0; x<220; ++x){
            line[x]=x+32;
        }        
        fpsCounter++;
        z_line = -88;
    }

    #define FIXPOINT 10 // change this for better accuracy
    #define yScale 16 // same as texture size?
    #define xScale 16
    #define tileWidth 31
    #define tileHeight 31
    
    int z_=0;
    int texOff=0;

    if(y<88){
        z_ = -z_line;
        texOff = 1024;
    }else{
        z_ = z_line;
    }


    int y_;
    if(z_) y_=(y*yScale << FIXPOINT) / z_;
    else y_=0;
    
    y_ = (y_ >> FIXPOINT) &tileHeight;
    int y2 = 2+32*y_;

    int xAdder;
    if(z_) xAdder = (xScale << FIXPOINT) / z_;
    else xAdder = 0;
    
    int x2 = -110 * xAdder;
    
    auto lineP = &Pokitto::Display::palette[32];
    //auto tilesP = &tiles[0];

    #define pix()\
        *lineP++ = floor_pal[floor_tile[texOff + y2 + (((x2+=xAdder) >> FIXPOINT)&tileWidth)]];

    for(int32_t x=0; x<220; x+=44){
        pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix();
        pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix();
        pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix();
        pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix(); pix();

    }
    z_line++;
}*/

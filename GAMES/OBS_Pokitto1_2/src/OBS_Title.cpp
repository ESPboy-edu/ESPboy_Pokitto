#include "OBS.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


PROGMEM const uint8_t textLengths[] = { 50, 51, 54, 61 };

PROGMEM const uint8_t IntroText_00[] = {    
    4,'Y','o','u','r',' ','s','h','i','p',' ','h','a','s',' ','b','e','e','n',
    7,'d','a','m','a','g','e','d',' ','b','y',' ','s','o','m','e',
    14,'s','p','a','c','e',' ','d','e','b','r','i','s','.','.',
    };

PROGMEM const uint8_t IntroText_01[] = {
    10,'.','.','t','h','e',' ','s','t','e','e','r','i','n','g',' ','i','s',
    3,'b','r','o','k','e','n',' ','a','n','d',' ','y','o','u',' ','c','a','n',
    18,'n','o','t',' ','n','a','v','i','g','a','t','e','.',
};

PROGMEM const uint8_t IntroText_02[] = {
    7,'Y','o','u',' ','d','i','s','c','o','v','e','r',' ','t','h','a','t',
    6,'b','y',' ','f','i','r','i','n','g',' ','t','h','e',' ','l','a','s','e','r',
    11,'y','o','u',' ','c','a','n',' ','s','t','e','e','r','.','.',
};

PROGMEM const uint8_t IntroText_03[] = {
    3,'.','.','s','o','r','t',' ','o','f','!',' ','A','v','o','i','d',' ','t','h','e',
    1,'a','s','t','e','r','o','i','d','s',' ','a','n','d',' ','e','n','e','m','y',
    4,'s','h','i','p','s',' ','a','n','d',' ','f','l','y',' ','h','o','m','e','.',
};

PROGMEM const uint8_t * const IntroTexts[] = { IntroText_00, IntroText_01, IntroText_02, IntroText_03 }; 

PROGMEM const uint8_t Spacing_Lower[] = {
    5,5,5,5,5,5,5,5,2,5,5,2,6,5,5,5,5,4,5,4,5,5,5,5,5,5
//  a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
};

PROGMEM const uint8_t Spacing_Upper[] = {
    5,5,5,5,5,5,5,5,3,5,5,3,6,5,5,5,5,4,5,4,5,5,5,5,5,5
//  a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
};

// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    gameState = GameState::Title;

    for (Asteroid &smallAsteroid : this->smallAsteroids) {

        smallAsteroid.setX(random(0, 256));
        smallAsteroid.setY(random(0, 56));
        smallAsteroid.setActive(true);
        
    }

    for (Asteroid &largeAsteroid : this->largeAsteroids) {

        this->launchLargeAsteroid(largeAsteroid);
        
    }

    for (Point &star : this->starfield) {

        star.setX(random(0, 110));
        star.setY(random(0, 88));
        
    }

    titleScreenVars.reset();
    player.reset();

    #ifdef SOUNDS
        this->playTheme(Theme::Main, true);
    #endif
}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {
    
    // if (PC::buttons.pressed(BTN_A)) {
    //     explode(55, 44, ExplosionSize::Small);
    // }
    
    // if (PC::buttons.pressed(BTN_B)) {
    //     explode(55, 44, ExplosionSize::Medium);
    // }
    
    // if (PC::buttons.pressed(BTN_C)) {
    //     explode(55, 44, ExplosionSize::Large);
    // }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {

        switch (titleScreenVars.mode) {

            case TitleMode::OBS:

                #ifdef SOUNDS
                    muteTheme();
                #endif

                titleScreenVars.mode = TitleMode::Scroll_One;
                titleScreenVars.counter = 88;
                break;

            case TitleMode::Scroll_One:
                titleScreenVars.mode = TitleMode::Scenario;
                titleScreenVars.counter = 88;
                break;

            case TitleMode::Scroll_Two:
                gameState = GameState::Game_Init; 
                break;

            default:
                break;

        }

    }



      
    // Move and render starfield ..

    moveRenderStarfield();
    PD::setColor(11);

    switch (titleScreenVars.mode) {

        case TitleMode::OBS:

            if (PC::buttons.pressed(BTN_UP)) { 

                this->cookie->sfx--;
                this->cookie->saveCookie();
                // this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    #ifdef SOUNDS
                        this->playTheme(Theme::Main, true);
                    #endif

                }

            }

            if (PC::buttons.pressed(BTN_DOWN)) { 

                this->cookie->sfx++;
                this->cookie->saveCookie();
                // this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    #ifdef SOUNDS
                        this->playTheme(Theme::Main, true);
                    #endif

                }

            }


            this->moveRenderSmallAsteroids(true);
            this->moveRenderLargeAsteroids(true);


            PD::drawBitmap(24, 26, Images::Title);

            // this->renderShockwave();
            // this->renderParticles();

            for (uint8_t i = 0; i < Constants::SmallAsteroid_Size; i++) {

                Asteroid &smallAsteroid = smallAsteroids[i];

                if (smallAsteroid.getActive()) {

                    if (i % 2 == 1) {
                        PD::drawBitmap(smallAsteroid.getX(), smallAsteroid.getY(), Images::SmallAsteroid);
                    }

                }
                
            }

            for (uint8_t i = 0; i < Constants::LargeAsteroid_Size; i++) {
            
                Asteroid &largeAsteroid = largeAsteroids[i];

                if (largeAsteroid.getActive()) {
                                
                    if (i % 2 == 1) {
                        PD::drawBitmap(largeAsteroid.getX(), largeAsteroid.getY(), Images::BigAsteroid[largeAsteroid.getType()]);
                    }

                }
                    
            }            

            switch (this->cookie->sfx) {

                case SoundEffects::Both:
                    PD::drawBitmap(95, 81, Images::Sound_Both_White);
                    break;

                case SoundEffects::None:
                    PD::drawBitmap(95, 81, Images::Sound_None_White);
                    break;

                case SoundEffects::SFX:
                    PD::drawBitmap(95, 81, Images::Sound_SFX_White);
                    break;

                case SoundEffects::Music:
                    PD::drawBitmap(95, 81, Images::Sound_Music_White);
                    break;

                
            }
            
            break;

        case TitleMode::Scroll_One:

            titleScreenVars.counter--;
            PD::drawBitmap(24, 26 - (88 - titleScreenVars.counter), Images::Title);
            PD::drawBitmap(3, 88 + 20 - (88 - titleScreenVars.counter), Images::Scenario);

            if (titleScreenVars.counter == 0) {

                titleScreenVars.mode = TitleMode::Scenario;

            }

            break;

        case TitleMode::Scenario:

            PD::drawBitmap(3, 20, Images::Scenario);

            if (titleScreenVars.index < textLengths[titleScreenVars.panel] && PC::frameCount % 6 == 0) {
                
                #ifdef SOUNDS                
                    playSoundEffect(SoundEffect::KeyPress);
                #endif

            }

            introText(20);

            break;

        case TitleMode::Scroll_Two:

            titleScreenVars.panel = 3;
            titleScreenVars.counter--;

            PD::drawBitmap(3, 20 - (88 - titleScreenVars.counter), Images::Scenario);
            introText(20 - (88 - titleScreenVars.counter));

            if (titleScreenVars.counter == 0) {

                titleScreenVars.mode = TitleMode::Entrance;
                titleScreenVars.counter = 0;

            }

            break;

        case TitleMode::Entrance:

            titleScreenVars.counter++;
            PD::drawBitmap(-16 + titleScreenVars.counter, player.getY(), Images::PlayerShip);
            PD::drawBitmap(-25 + titleScreenVars.counter, player.getY() + 3, Images::ShipParticle[PC::frameCount % 8 < 4]);

            if (titleScreenVars.counter == 25) {

                gameState = GameState::Game_Init;

            }

            break;

    }

}


void Game::introText(int8_t y) {

    uint8_t line = 0;
    uint8_t x = 0;

    for (uint8_t i = 0; i < titleScreenVars.index; i++) {

        uint8_t c = IntroTexts[titleScreenVars.panel][i];

        switch (c) {

            case 0 ... 31:
                line++;
                x = 0 + c;
                break;

            case ' ':
                x = x + 3;
                // x = x + 4;
                break;
            
            default:
                PD::setCursor(11 + x, y + (line * 10));
                PD::print(static_cast<char>(c));

                switch (c) {

                    case 'A' ... 'Z':
                        x = x + Spacing_Upper[c - 'A'];
                        break;

                    case 'a' ... 'z':
                        x = x + Spacing_Lower[c - 'a'];
                        break;

                    case '.':
                        x = x + 3;
                        break;
                
                    default:
                        x = x + 5;
                        break;
                }

                break;

        }
        
    }

    if (titleScreenVars.index < textLengths[titleScreenVars.panel] && PC::frameCount % 2 == 0) {

        titleScreenVars.index++;

    }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {
        
        if (titleScreenVars.index == textLengths[titleScreenVars.panel] && titleScreenVars.skipTypewriter == false) {
            titleScreenVars.panel++;
            titleScreenVars.index = 0;
        }
        else {
            if (titleScreenVars.skipTypewriter) titleScreenVars.panel++;
            titleScreenVars.skipTypewriter = true;
            titleScreenVars.index = textLengths[titleScreenVars.panel];
        }

        if (titleScreenVars.panel == 4) {
            titleScreenVars.panel = 3;
            titleScreenVars.mode = TitleMode::Scroll_Two;
            titleScreenVars.counter = 88;
            titleScreenVars.index = textLengths[3];
        }

    }

}

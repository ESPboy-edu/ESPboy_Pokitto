#pragma once

#include <stdint.h>
#include "Pokitto.h"



void initGame();
void mainMenu();
void printCentered(const char* text);
void popup(const char* text);
void popup(const char* text, uint8_t duration);
void updatePopup();
void print_border(int16_t x,int16_t y,const char* text,uint8_t cf,uint8_t cb);

void drawAll();
void drawCompass();

void loadEEPROM();
void saveEEPROM();

void _init();
void _gameloop();
void _gamesetup();

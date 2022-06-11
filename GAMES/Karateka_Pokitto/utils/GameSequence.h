#pragma once

#include "Enums.h"

#define GAME_STATE_SEQ_SIZE                       13

PROGMEM const uint8_t gameSequence[] = {
  
  //                                      Delay   IntArch     Launch      Show        Enemy               Interior = 0,     MinXDist,   XposOverall              ImmediateAction                 RetreatAction               Kick or Punch           Crowder?
  //                                              1 = LH1     Enemies     Crevice     Activity            Exterior = 1                                           How frequently will the         How frequently will                                 Does the enemy move
  //                                              2 = RH1     1=Person1               255 Slow / 0 Fast   Dungeon = 2                                            enemy blindly kick or           the enemy simply back                               forward frequently
  //                                              3 = LH2     2=Person2                                                                                          punch?  Less frequently         away from the player -                              or not?  
  //                                              4 = RH2     3=Person3                                                                                          allows player to attack         even if not too close?
  //                                              5 = LH3     4=Emperor                                                                                          more.
  //                                              6 = RH3     5=Eagle 
  //                                              5 = LH4     6=KickDoor             
  //                                              6 = RH4      
  //                                              9 = LH Gate                 
  //                                             10 = RH Gate  
  //                                             11 = LH Entr  
  //                                             12 = RH Entr
  //                                             13 = 
  //                                             14 = 
  //                                             15 = LHS Stairs 
  
    GAME_STATE_TITLE_SCENE_INIT,            0,      0,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_INTRO_TEXT_INIT,             0,      0,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_CASTLE_SCENE_INIT,          25,      0,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PRINCESS_BANISHMENT,       210,      0,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENTRANCE_INIT,               0,      0,          0,          1,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                  25,      0,          0,          1,          0,                  1,            125,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          1,          0,         80,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_NORMAL,      ACTION_KICK_PREF,       MOVE_FWD_INFREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          1,          0,         80,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_NORMAL,      ACTION_KICK_PREF,       MOVE_FWD_INFREQUENT,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          1,          0,         75,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_FREQUENT,    ACTION_PUNCH_PREF,      MOVE_FWD_NORMAL,
    GAME_STATE_PLAY_INIT,                   0,      0,          1,          0,         75,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_FREQUENT,    ACTION_PUNCH_PREF,      MOVE_FWD_NORMAL,
    GAME_STATE_GO_THROUGH_GATE,             0,      6,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                   25,     5,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          1,          0,         75,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_INFREQUENT,  ACTION_NO_PREF,         MOVE_FWD_NORMAL,
    GAME_STATE_PLAY_INIT,                   0,      0,          1,          0,         75,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_INFREQUENT,    RETREAT_ACTION_INFREQUENT,  ACTION_NO_PREF,         MOVE_FWD_NORMAL,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          1,          0,         70,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_NORMAL,        RETREAT_ACTION_NORMAL,      ACTION_PUNCH_PREF,      MOVE_FWD_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          1,          0,         70,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_NORMAL,        RETREAT_ACTION_NORMAL,      ACTION_PUNCH_PREF,      MOVE_FWD_FREQUENT,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          1,          0,         65,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_NORMAL,        RETREAT_ACTION_FREQUENT,    ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          1,          0,         65,                  1,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_NORMAL,        RETREAT_ACTION_FREQUENT,    ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_GO_THROUGH_GATE,             0,     12,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PRINCESS_SITTING,           18,      0,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                  20,     13,          0,          0,          0,                  0,             75,          16,                      0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                   0,      0,          5,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                   0,      0,          5,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_EMPEROR_INIT,                0,      0,          5,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          2,          0,         65,                  0,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_NORMAL,      ACTION_NO_PREF,         MOVE_FWD_INFREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          2,          0,         65,                  0,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_NORMAL,      ACTION_NO_PREF,         MOVE_FWD_INFREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          5,          0,         60,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          2,          0,         55,                  0,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_FREQUENT,    ACTION_PUNCH_PREF,      MOVE_FWD_INFREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          2,          0,         55,                  0,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_FREQUENT,    ACTION_PUNCH_PREF,      MOVE_FWD_NORMAL,
    GAME_STATE_GO_THROUGH_GATE,             0,     10,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PRINCESS_SITTING,           18,      0,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                  30,     15,          0,          0,          0,                  2,             50,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          3,          0,         55,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_INFREQUENT,  ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          3,          0,         55,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_INFREQUENT,  ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          3,          0,         55,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_INFREQUENT,  ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          3,          0,         55,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_FREQUENT,      RETREAT_ACTION_INFREQUENT,  ACTION_KICK_PREF,       MOVE_FWD_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          5,          0,          0,                  2,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_PLAY_INIT,                   0,      0,          5,          0,          0,                  2,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_ENEMY_APPROACH_INIT,         0,      0,          4,          0,         50,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_V_FREQUENT,     RETREAT_ACTION_FREQUENT,   ACTION_NO_PREF,         MOVE_FWD_V_FREQUENT,
    GAME_STATE_PLAY_INIT,                   0,      0,          4,          0,         50,                  2,              0,          XPOSOVERALL_NO_CHANGE,   IMMEDIATE_ACTION_V_FREQUENT,     RETREAT_ACTION_FREQUENT,   ACTION_NO_PREF,         MOVE_FWD_V_FREQUENT,
    GAME_STATE_GO_THROUGH_GATE,             0,      2,          6,          0,          0,                  2,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_FINAL_SCENE_INIT,            0,      0,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_EXTRO_TEXT_INIT,             0,      0,          0,          0,          0,                  1,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,
    GAME_STATE_THE_END,                     0,      0,          0,          0,          0,                  0,              0,          XPOSOVERALL_NO_CHANGE,   0,                              0,                          0,                      0,

};
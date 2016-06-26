//
//  definitions.h
//  SpacePewPew
//
//  Created by BIBIN THOMAS on 6/5/16.
//
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SCENE_TRANSITION 2.5
#define GAME_TRANSISTION 0.25

//Cocos studio variables - these are the names from the cocos studio
#define CCS_BG_SPRITE_ONSCREEN "starBackground1"
#define CCS_BG_SPRITE_TOP_OF_SCREEN "starBackground2"
#define CCS_BG_SPRITE_BOTTOM_OF_SCREEN "starBackground3"
#define CCS_STOP_BUTTON "StopButton"
#define CCS_PAUSE_BUTTON "PauseButton"
#define CCS_ASTEROID_LAYER "AsteroidLayer"
#define CCS_PLAYER_SHIP "PlayerShip"
#define CCS_CLOSE_BUTTON "CloseButton"
#define CCS_TICK_BUTTON "TickButton"
#define CCS_LEFTMOVE_BUTTON "LeftMoveButton"
#define CCS_RIGHTMOVE_BUTTON "RightMoveButton"

//ship left and right sprites
#define SHIP_RIGHT_MOVE "res/png/playerRight.png"
#define SHIP_LEFT_MOVE "res/png/playerLeft.png"
#define SHIP_CENTER "res/png/player.png"



// Asteroid rotation angles and delay variables
#define ASTEROID_DELAY_TIME 9
#define ASTEROID_ROTATION_MIN_ANGLE 360
#define ASTEROID_ROTATION_MAX_ANGLE 750

#define ASTEROID_ROT_MIN_DELAY 0
#define ASTEROID_ROT_MAX_DELAY 3

//Screen Parallax effects
#define SCREEN_BG_DOWNSCROLL_SPEED 7

//Asteroid Parallax effects
#define ASTEROID_DOWNSCROLL_SPEED (SCREEN_BG_DOWNSCROLL_SPEED - 2)

#define SHIP_MOVE_SPEED 10

#define RED_LASER "res/png/laserRed.png"





#endif /* DEFINITIONS_H */

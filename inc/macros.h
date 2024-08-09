#ifndef MACROS_H
#define MACROS_H

// #ifndef __OSX__
//
// typedef enum s_keys {
//
//   W_KEY = 0x77,
//   S_KEY = 0x73,
//   A_KEY = 0x61,
//   D_KEY = 0x64,
//   LEFT_KEY = 0xFF51,
//   RIGHT_KEY= 0xFF53, 
//   J_KEY = 0x6a,
//   K_KEY = 0x6b,
//   ESC_KEY = 0xFF1B,
// } t_keys;


typedef enum s_keys {
  W_KEY = 0x0D,
  S_KEY = 0x01,
  A_KEY = 0x00,
  D_KEY = 0x02,
  J_KEY = 0x6a,
  K_KEY = 0x6b,
  LEFT_KEY = 0x7B,
  RIGHT_KEY= 0x7C, 
  ESC_KEY = 0x35,
} t_keys;


#define NIL 0
#define COLOR 0xFF5733
#define GREEN 0x00FF4D
#define VER false
#define COLLISION_MARGIN 7 
#define PLAYER_SIZE 10.0
#define HOR true
#define FPS 100000
#define TILE_SIZE 64
#define MAP_TILE_SIZE 10
#define MOVE_SPEED 2
#define HIT_BOX 10
#define SCALE_FACTOR 0.7
# define SCREEN_WIDTH 1980 
# define SCREEN_HEIGHT 1280
# define TITLE "cub3D"
#define DEFAULT_ELEMENT_WIDTH 300
#define DEFAULT_ELEMENT_HEIGHT 100
#endif

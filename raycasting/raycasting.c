
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include <stdio.h>

void render_player(t_info *info) {
  drawcircle(info->player->vector.start.x, info->player->vector.start.y, HIT_BOX, info->mlx);
}

// void update_player_dir(t_map *map, int i, int j) {
//   if (map->map[i][j] == 'N') {
//     map->player->player_dir = north;
//   }
//   if (map->map[i][j] == 'W')
//     map->player->player_dir = west;
//   if (map->map[i][j] == 'S')
//     map->player->player_dir = south;
//   if (map->map[i][j] == 'E')
//     map->player->player_dir = east;
// }

void print_point(t_point point) {
  printf("x = %f\n", point.x);
  printf("y = %f\n", point.y);
}



// void fps(t_map *map) {
//   static int frames = 0;
//   char *string;
//   t_mlx *mlx = map->mlx;
//
//   string = ft_itoa(frames);
//   mlx_string_put(mlx->mlx, mlx->mlx_win, 150, 50, COLOR, string);
//   mlx_string_put(mlx->mlx, mlx->mlx_win, 40, 50, COLOR, "frames :");
//   if (frames == 60)
//     frames = 0;
//   else
//     frames++;
//   free(string);
// }

void reset_player_info(t_player *player) {
    player->position.x = 0;
    player->position.y = 0;
    
}


void raycaster(t_info *info) { 
    // t_player    *player = info->player;

    
    test_cast(info);

    // cast_rays(info->map); 

}

void renderer(t_info *info) {

  // t_menu *menu;
  // t_map *map;
  // t_player *player = info->player;

  // map = info->map;
  // map->player = player;
  // menu = map->current_menu;
  t_mlx *mlx = info->mlx;
  // fprintf(stderr,"mlx = %p\n", mlx->mlx);
  // menu->mlx = mlx;
  // clear_window(mlx);

  // gui_entry_point(menu);
  // fps(map);
  // map_tile_morph(map);
  // render_player(map);
  raycaster(info);
  //render routine.
  mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, info->img.img, 0, 0);
  usleep(5000);

  // reset_player_info(player);
}

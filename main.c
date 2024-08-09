
#include "inc/defines.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

void free_arr(char **arr) {
  int i = 0;
  while (arr[i] != NULL) {
    free(arr[i]);
  }
}

void free_all(t_info *info) {

  void *mlx;
  void *mlx_win;

  mlx = info->mlx->mlx;
  mlx_win = info->mlx->mlx_win;

  mlx_destroy_window(mlx, mlx_win);
  // free_arr(info->map->map);
  // free(info->map);
  free(info->player);
  free(info);
  exit(EXIT_FAILURE);
}






void key_hook(int key, t_info *info)
{
  if (key == ESC_KEY)
    free_all(info);
  else {
    handle_player_movement(info, key);
  }
}

void new_window(t_mlx *mlx) {

  mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}


void new_image(t_info *info) {
  info->img.addr = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int get_offset(t_img *image, t_point pixel)
{
  int x = pixel.x;
  int y = pixel.y;
  x = x % 64;
  y = y % 64;
  int offset = (y * image->line_length + x * (image->bits_per_pixel / 8));
  return (offset);
}

bool game_init(t_info *info) {

  t_mlx *mlx;

  mlx = info->mlx;

  t_img image;

  new_window(info->mlx);

  image.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (image.img == NULL)
    return false;
  image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length,
                                 &image.endian);
  info->img = image;

  mlx_hook(mlx->mlx_win, 2, 1L << 0, (void *)key_hook, info);
  mlx_loop_hook(mlx->mlx, (void *)renderer, info);
  mlx_loop(mlx->mlx);
  return true;
}

void init_mlx(t_mlx *mlx) { mlx->mlx = mlx_init(); }

t_info *vars_init(int ac, char **av) {

  t_data *data;
  t_info *info;

  data = parse_entry(ac, av);
  info = malloc(sizeof(t_info));
  info->data = data;
  info->mlx = data->ini;
  info->map = data->map;
  info->player = player_init();

  return (info);
}

int main(int ac, char **av) {
  game_init(vars_init(ac, av));
  return 1;
}

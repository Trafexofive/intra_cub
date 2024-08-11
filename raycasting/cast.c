
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include "../inc/defines.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// double  angle_add(double angle, double angle_to_add)
// {
//     double new_angle = (angle + angle_to_add) ;
//     new_angle = new_angle % 360.0;
//
//     return (new_angle);
// }

void fill_image(t_info *info, int color) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;
  while (point.y < SCREEN_HEIGHT) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, color);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

void draw_wall_strip(t_info *info, int x, double dist, double angle) {
  t_img *image = &info->img;
  t_point point;
  int color;
  double corrected_dist = dist * cos(angle - info->player->angle);
  double wall_height = (SCREEN_HEIGHT / corrected_dist) * TILE_SIZE;
  int draw_start = (SCREEN_HEIGHT - wall_height) / 2;
  if (draw_start < 0)
    draw_start = 0;
  int draw_end = (SCREEN_HEIGHT + wall_height) / 2;
  if (draw_end >= SCREEN_HEIGHT)
    draw_end = SCREEN_HEIGHT - 1;
  info->wall_h = wall_height;

  // Calculate texture x coordinate
  double wall_x = info->player->x + corrected_dist * cos(angle);
  wall_x -= floor(wall_x);
  int tex_x = (int)(wall_x * TEXTURE_WIDTH);

  point.x = x;
  double step = 1.0 * TEXTURE_HEIGHT / wall_height;
  double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;

  for (int y = draw_start; y <= draw_end; y++) {
    int tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
    tex_pos += step;
    point.y = y;
    color = get_tex_pixel_color(info, tex_x, tex_y);
    put_pixel(image, point, color);
  }
}

int get_tex_pixel_color(t_info *info, int tex_x, int tex_y) {
  t_img *texture;
  
  // Select the appropriate texture based on wall side
  if (info->wall_side == 'N')
    texture = &info->north_texture;
  else if (info->wall_side == 'S')
    texture = &info->south_texture;
  else if (info->wall_side == 'E')
    texture = &info->east_texture;
  else if (info->wall_side == 'W')
    texture = &info->west_texture;
  else
    return 0xFFFFFF; // Default white color if no texture is found

  // Calculate the position in the texture's data
  char *dst = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
  
  // Return the color as an integer
  return *(unsigned int*)dst;
}

// void draw_wall_strip(t_info *info, int x, double dist, double angle) {
//   t_img *image = &info->img;
//   t_point point;
//   int color;
//
//   double corrected_dist = dist * cos(angle - info->player->angle);
//
//   double wall_height = (SCREEN_HEIGHT / corrected_dist) * TILE_SIZE;
//   int draw_start = (SCREEN_HEIGHT - wall_height) / 2;
//   if (draw_start < 0)
//     draw_start = 0;
//   int draw_end = (SCREEN_HEIGHT + wall_height) / 2;
//   if (draw_end >= SCREEN_HEIGHT)
//     draw_end = SCREEN_HEIGHT - 1;
//     info->wall_h = wall_height;
//
//
//   if (info->wall_side == 'N') {
//     color = 0xFF0000;
//   } else if (info->wall_side == 'S') {
//     color = 0x00FF00;
//   } else if (info->wall_side == 'E') {
//     color = 0x0000FF;
//   } else if (info->wall_side == 'W') {
//     color = 0xFFFF00;
//   } else {
//     color = 0xFFFFFF;
//   }
//   point.x = x;
//   int y = draw_start;
//   while (y <= draw_end) {
//     point.y = y;
//     //color = get_tex_pixel_color(&point, info);
//     put_pixel(image, point, color);
//     y++;
//   }
// }
//
void put_floor_color(t_info *info, int color) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = SCREEN_HEIGHT / 2;
  while (point.y < SCREEN_HEIGHT) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, color);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

void put_skye_color(t_info *info, int color) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;
  while (point.y < SCREEN_HEIGHT / 2) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, color);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

void clear_image(t_info *info) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;
  while (point.y < SCREEN_HEIGHT) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, 0);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

void render_map(t_info *info) {
  t_img *image = &info->img;
  t_point point;

  char **map = info->map;
  int y = 0;
  while (map[y]) {
    int x = 0;
    while (map[y][x]) {
      if (map[y][x] == '1') {
        int dy = 0;
        while (dy < MAP_TILE_SIZE) {
          int dx = 0;
          while (dx < MAP_TILE_SIZE) {
            point.x = x * MAP_TILE_SIZE + dx;
            point.y = y * MAP_TILE_SIZE + dy;
            put_pixel(image, point, COLOR);
            dx++;
          }
          dy++;
        }
      } else {
        point.x = info->player->vector.start.x / MAP_TILE_SIZE;
        point.y = info->player->vector.start.y / MAP_TILE_SIZE;
        put_pixel(image, point, GREEN);
      }
      x++;
    }
    y++;
  }
}

void set_player_spawn(t_info *info) {
  char **map = info->map;
  int i = 0;
  int j = 0;

  while (map[j]) {
    while (map[j][i]) {
      if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' ||
          map[j][i] == 'E') {
        info->player->vector.start.x = i * TILE_SIZE + TILE_SIZE / 2;
        info->player->vector.start.y = j * TILE_SIZE + TILE_SIZE / 2;
        return;
      }
      i++;
    }
    i = 0;
    j++;
  }
}
double raycast(t_point pos, double angle, t_vector *vector, t_info *info) {

  t_point dir = {cos(angle), sin(angle)};

  t_point ray_step = {fabs(TILE_SIZE / dir.x), fabs(TILE_SIZE / dir.y)};
  int map_x = (int)(pos.x / TILE_SIZE);
  int map_y = (int)(pos.y / TILE_SIZE);
  t_point ray_len;
  t_point step;
  char **map = info->map;

  if (dir.x < 0) {
    step.x = -1;
    ray_len.x = (pos.x - map_x * TILE_SIZE) * ray_step.x / TILE_SIZE;
  } else {
    step.x = 1;
    ray_len.x = ((map_x + 1) * TILE_SIZE - pos.x) * ray_step.x / TILE_SIZE;
  }
  if (dir.y > 0) {
    step.y = 1;
    ray_len.y = ((map_y + 1) * TILE_SIZE - pos.y) * ray_step.y / TILE_SIZE;
  } else {
    step.y = -1;
    ray_len.y = (pos.y - map_y * TILE_SIZE) * ray_step.y / TILE_SIZE;
  }
  // info->wall_side = (dir.x < 0) ? 'W' : 'E';
  // info->wall_side = (dir.y < 0) ? 'N' : 'S';

  int hit = 0;
  double dist = 0;
  while (!hit && map_x >= 0 && map_y >= 0) {

    if (ray_len.x < ray_len.y) {

      map_x += step.x;
      dist = ray_len.x;
      ray_len.x += ray_step.x;
      info->wall_side = (dir.x < 0) ? 'W' : 'E';
    } else {
      map_y += step.y;
      dist = ray_len.y;
      ray_len.y += ray_step.y;
      info->wall_side = (dir.y < 0) ? 'N' : 'S';
    }
    if (map_x >= 0 && map_y >= 0) {
      if (map[map_y][map_x] != '0' && map[map_y][map_x] != 'N' &&
          map[map_y][map_x] != 'S' && map[map_y][map_x] != 'W' &&
          map[map_y][map_x] != 'E') {
        hit = 1;
      }
    }
  }

  int end_x = pos.x + dir.x * dist;
  int end_y = pos.y + dir.y * dist;
  vector->start = pos;
  vector->end.x = end_x;
  vector->end.y = end_y;

  return dist;
}

void test_cast(t_info *info) {
  if (info->player->vector.len == -1) {
    set_player_spawn(info);
    info->player->vector.len = -2;
  }
  t_player *player = info->player;
  double dist;
  t_vector vector;
  clear_image(info);

  put_floor_color(info, GREEN);
  put_skye_color(info, 0x000FA);
  
  //preload both funcs in images and just out them at first.
  double fov = player->fov;
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    double ray_angle =
        player->angle - fov / 2 + (x / (double)SCREEN_WIDTH) * fov;
    dist = raycast(info->player->vector.start, ray_angle, &vector, info);
    // dist = dist;
    // printf("vector start = %f, %f\n", vector.start.x, vector.start.y);
    draw_wall_strip(info, x, dist, ray_angle);
  }
  render_map(info);
  // drawcircle(vector.start.x / MAP_TILE_SIZE, vector.start.y / MAP_TILE_SIZE, 13,
  //            info->mlx);
  // put_pixel(info->img.img, player->vector.start, GREEN); //
  // COLOR_WALL for walls render_player(info); // needs to be implemented with
  // new pixel put

  if (player->angle > 2 * M_PI)
    player->angle -= 2 * M_PI;

  // printf("p angle : %f\n", player->angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:06:56 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 14:42:35 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <mlx.h>

void calculate_wall_dimensions(t_info *info, double dist, double angle) {
    double corrected_dist = dist * cos(angle - info->player->angle);
    double wall_height = (SCREEN_HEIGHT / corrected_dist) * TILE_SIZE;
    int draw_start = (SCREEN_HEIGHT - wall_height) / 2;
    int draw_end = (SCREEN_HEIGHT + wall_height) / 2;
    
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    
    info->dis = corrected_dist;
    info->wall_h = wall_height;
    info->draw_start = draw_start;
    info->draw_end = draw_end;
}

void draw_wall_column(t_info *info, int x, t_point p) {
    t_img *image = &info->img;
    t_point point;
    point.x = x;
    
    for (int y = info->draw_start; y <= info->draw_end; y++) {
        if (y < 0 || y >= SCREEN_HEIGHT) continue;
        
        int y2 = ((y - info->draw_start) * 100) / info->wall_h;
        point.y = y;
        int color = get_tex_pixel_color(y2, info, p);
        put_pixel(image, point, color);
    }
}

void draw_wall_strip(t_info *info, int x, double dist, double angle, t_point p) {
    calculate_wall_dimensions(info, dist, angle);
    draw_wall_column(info, x, p);
}


// void draw_wall_strip(t_info *info, int x, double dist, double angle,
//                      t_point p) {
//   t_img *image;
//   t_point point;
//   int color;
//   double corrected_dist;
//   double wall_height;
//   int draw_start;
//   int draw_end;
//   int y;
//   int y2;
//
//   image = &info->img;
//   corrected_dist = dist * cos(angle - info->player->angle);
//   wall_height = (SCREEN_HEIGHT / corrected_dist) * TILE_SIZE;
//   info->wall_h = wall_height;
//   draw_start = (SCREEN_HEIGHT - wall_height) / 2;
//   draw_end = (SCREEN_HEIGHT + wall_height) / 2;
//   if (draw_end >= SCREEN_HEIGHT)
//     draw_end = SCREEN_HEIGHT - 1;
//   info->dis = corrected_dist;
//   info->wall_h = wall_height;
//   info->draw_start = draw_start;
//   info->draw_end = draw_end;
//   point.x = x;
//   y = draw_start;
//   while (y <= draw_end) {
//     y2 = ((y - draw_start) * 100) / wall_height;
//     point.y = y;
//     if (y < 0 || y > SCREEN_HEIGHT) {
//       y++;
//       continue;
//     }
//     color = get_tex_pixel_color(y2, info, p);
//     put_pixel(image, point, color);
//     y++;
//   }
// }

void put_floor_color(t_info *info, int color) {
  t_img *image;
  t_point point;

  image = &info->img;
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
  t_img *image;
  t_point point;

  image = &info->img;
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

void set_player_spawn(t_info *info) {
  char **map;
  int i;
  int j;

  map = info->map;
  i = 0;
  j = 0;
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
void initialize_ray(t_point pos, double angle, t_point *dir, t_point *ray_step, t_point *ray_len, t_point *step, int *map_x, int *map_y) {
    dir->x = cos(angle);
    dir->y = sin(angle);
    ray_step->x = fabs(TILE_SIZE / dir->x);
    ray_step->y = fabs(TILE_SIZE / dir->y);
    *map_x = (int)(pos.x / TILE_SIZE);
    *map_y = (int)(pos.y / TILE_SIZE);

    if (dir->x < 0) {
        step->x = -1;
        ray_len->x = (pos.x - *map_x * TILE_SIZE) * ray_step->x / TILE_SIZE;
    } else {
        step->x = 1;
        ray_len->x = ((*map_x + 1) * TILE_SIZE - pos.x) * ray_step->x / TILE_SIZE;
    }
    if (dir->y > 0) {
        step->y = 1;
        ray_len->y = ((*map_y + 1) * TILE_SIZE - pos.y) * ray_step->y / TILE_SIZE;
    } else {
        step->y = -1;
        ray_len->y = (pos.y - *map_y * TILE_SIZE) * ray_step->y / TILE_SIZE;
    }
}

int perform_dda(t_info *info, t_point *dir, t_point *ray_len, t_point *ray_step, t_point *step, int *map_x, int *map_y, double *dist) {
    int hit = 0;
    char **map = info->map;

    while (!hit && *map_x >= 0 && *map_y >= 0) {
        if (ray_len->x < ray_len->y) {
            *map_x += step->x;
            *dist = ray_len->x;
            ray_len->x += ray_step->x;
            info->wall_side = (dir->x < 0) ? 'W' : 'E';
        } else {
            *map_y += step->y;
            *dist = ray_len->y;
            ray_len->y += ray_step->y;
            info->wall_side = (dir->y < 0) ? 'N' : 'S';
        }
        if (*map_x >= 0 && *map_y >= 0) {
            if (map[*map_y][*map_x] != '0' && map[*map_y][*map_x] != 'N' &&
                map[*map_y][*map_x] != 'S' && map[*map_y][*map_x] != 'W' &&
                map[*map_y][*map_x] != 'E') {
                hit = 1;
            }
        }
    }
    return hit;
}

double raycast(t_point pos, double angle, t_vector *vector, t_info *info) {
    t_point dir, ray_step, ray_len, step;
    int map_x, map_y;
    double dist = 0;

    initialize_ray(pos, angle, &dir, &ray_step, &ray_len, &step, &map_x, &map_y);
    perform_dda(info, &dir, &ray_len, &ray_step, &step, &map_x, &map_y, &dist);

    int end_x = (int)(pos.x + dir.x * dist) % TILE_SIZE;
    int end_y = (int)(pos.y + dir.y * dist);

    vector->start = pos;
    vector->end.x = end_x;
    vector->end.y = end_y;

    return dist;
}

// double raycast(t_point pos, double angle, t_vector *vector, t_info *info) {
//   t_point dir;
//   t_point ray_step;
//   int map_x;
//   int map_y;
//   t_point ray_len;
//   t_point step;
//   char **map;
//   int hit;
//   double dist;
//   int end_x;
//   int end_y;
//
//   dir.x = cos(angle);
//   dir.y = sin(angle);
//   ray_step.x = fabs(TILE_SIZE / dir.x);
//   ray_step.y = fabs(TILE_SIZE / dir.y);
//   map_x = (int)(pos.x / TILE_SIZE);
//   map_y = (int)(pos.y / TILE_SIZE);
//   map = info->map;
//   if (dir.x < 0) {
//     step.x = -1;
//     ray_len.x = (pos.x - map_x * TILE_SIZE) * ray_step.x / TILE_SIZE;
//   } else {
//     step.x = 1;
//     ray_len.x = ((map_x + 1) * TILE_SIZE - pos.x) * ray_step.x / TILE_SIZE;
//   }
//   if (dir.y > 0) {
//     step.y = 1;
//     ray_len.y = ((map_y + 1) * TILE_SIZE - pos.y) * ray_step.y / TILE_SIZE;
//   } else {
//     step.y = -1;
//     ray_len.y = (pos.y - map_y * TILE_SIZE) * ray_step.y / TILE_SIZE;
//   }
//   hit = 0;
//   dist = 0;
//   while (!hit && map_x >= 0 && map_y >= 0) {
//     if (ray_len.x < ray_len.y) {
//       map_x += step.x;
//       dist = ray_len.x;
//       ray_len.x += ray_step.x;
//       if (dir.x < 0 == true)
//         info->wall_side = 'W';
//       else
//         info->wall_side = 'E';
//     } else {
//       map_y += step.y;
//       dist = ray_len.y;
//       ray_len.y += ray_step.y;
//       if (dir.y < 0 == true)
//         info->wall_side = 'N';
//       else
//         info->wall_side = 'S';
//     }
//     if (map_x >= 0 && map_y >= 0) {
//       if (map[map_y][map_x] != '0' && map[map_y][map_x] != 'N' &&
//           map[map_y][map_x] != 'S' && map[map_y][map_x] != 'W' &&
//           map[map_y][map_x] != 'E') {
//         hit = 1;
//       }
//     }
//   }
//   end_x = pos.x + dir.x * dist;
//   end_x = end_x % TILE_SIZE;
//   end_y = pos.y + dir.y * dist;
//   vector->start = pos;
//   vector->end.x = end_x;
//   vector->end.y = end_y;
//   return (dist);
// }
//
void test_cast(t_info *info) {
  t_player *player;
  double dist;
  t_vector vector;
  double fov;
  int x;
  double ray_angle;

  if (info->player->vector.len == -1) {
    set_player_spawn(info);
    info->player->vector.len = -2;
  }
  player = info->player;
  clear_window(info->mlx);
  put_floor_color(info, info->data->color_f);
  put_skye_color(info, info->data->color_c);
  fov = player->fov;
  x = 0;
  while (x < SCREEN_WIDTH) {
    ray_angle = player->angle - fov / 2 + (x / (double)SCREEN_WIDTH) * fov;
    dist = raycast(info->player->vector.start, ray_angle, &vector, info);
    draw_wall_strip(info, x, dist, ray_angle, vector.end);
    x++;
  }
  if (player->angle > 2 * M_PI)
    player->angle -= 2 * M_PI;
}

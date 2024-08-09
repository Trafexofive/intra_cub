
#ifndef DEFINES_H
#define DEFINES_H

#include "struct.h"

void update_player_position(t_info *info, double move_speed,
                            double strafe_speed);
void check_collision(t_info *info, t_point move, t_point strafe, t_point new);
void handle_player_movement(t_info *info, int key) ;
int get_offset(t_img *image, t_point pixel) ;

#endif

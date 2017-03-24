/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:43 by dpanov            #+#    #+#             */
/*   Updated: 2017/02/28 16:24:44 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void ss(t_coord **tmp, int i)
{
    t_coord *sub;

    sub = (*tmp);
    while ((*tmp)->next != NULL)
    {
        if ((*tmp)->z > 1 && i == -1)
            (*tmp)->z += i;
        else if ((*tmp)->z > 0 && i != -1 )
            (*tmp)->z += i;
        (*tmp) = (*tmp)->next;
    }
    (*tmp) = sub;
}

void rot_matrix(t_data **data)
{
	(*data)->x_home = (((*data)->center_x + ((*data)->tmp->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp->y - (*data)->center_y) * sin((*data)->oz)));
	(*data)->y_home = (((*data)->center_y + ((*data)->tmp->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp->x - (*data)->center_x) * sin((*data)->oz)));
	(*data)->x_offset = (((*data)->center_x + ((*data)->tmp->next->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp->next->y - (*data)->center_y) * sin((*data)->oz)));
	(*data)->y_offset = (((*data)->center_y + ((*data)->tmp->next->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp->next->x - (*data)->center_x) * sin((*data)->oz)));
    (*data)->x_home = (((*data)->center_x + ((*data)->x_home - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp->z * sin((*data)->oy)));
    (*data)->x_offset = (((*data)->center_x + ((*data)->x_offset - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp->next->z * sin((*data)->oy)));
    (*data)->y_home = (((*data)->center_y + ((*data)->y_home - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp->z * sin((*data)->ox)));
    (*data)->y_offset = (((*data)->center_y + ((*data)->y_offset - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp->next->z * sin((*data)->ox)));
    (*data)->x_offset_vert = (((*data)->center_x + ((*data)->tmp_vert->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp_vert->y - (*data)->center_y) * sin((*data)->oz)));
    (*data)->y_offset_vert = (((*data)->center_y + ((*data)->tmp_vert->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp_vert->x - (*data)->center_x) * sin((*data)->oz)));
    (*data)->x_offset_vert = (((*data)->center_x + ((*data)->x_offset_vert - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp_vert->z * sin((*data)->oy)));
    (*data)->y_offset_vert = (((*data)->center_y + ((*data)->y_offset_vert - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp_vert->z * sin((*data)->ox)));
}

void	ft_put_px(t_data **data, int y, int x, int i)
{
	int p;

	p = (x * 4) + (y * 5120);
	if ( p >= 0 && p < (3686400) && x < 1280 && y < 720 && x > 0)
	{
        (*data)->data[p] = 200;
        (*data)->data[p + 1] = 80;
        (*data)->data[p + 2] = 255;
        if ((*data)->tmp->color  && i == 1){
            (*data)->data[p] = (*data)->tmp->b;
            (*data)->data[p + 1] = (*data)->tmp->g;
            (*data)->data[p + 2] = (*data)->tmp->r;
        } else if (((*data)->tmp_vert->color)){
            (*data)->data[p] = (*data)->tmp_vert->b;
            (*data)->data[p + 1] = (*data)->tmp_vert->g;
            (*data)->data[p + 2] = (*data)->tmp_vert->r;
        }
    }
}

void	ft_create_image(t_data **data, int n)
{
	int		sizeline;
	int		endian;
	int		bpp;

	if (n == 1)
	{
		(*data)->img = mlx_new_image((*data)->mlx, (*data)->img_size_x, (*data)->img_size_y);
		(*data)->data = mlx_get_data_addr((*data)->img, &bpp, &sizeline, &endian);
	}
	if (n == 2)
	{
		mlx_put_image_to_window((*data)->mlx, (*data)->win, (*data)->img, 0, 0);
		mlx_destroy_image((*data)->mlx, (*data)->img);
	}
	if (n == 3)
	{
		if ((*data)->data)

		mlx_destroy_image((*data)->mlx, (*data)->img);
	}
}

void data_reload(t_data **data)
{
    t_coord *tmp;
    (*data)->tmp = (*data)->head;
    (*data)->oz = ((*data)->oz_mod * M_PI) / 180;
    (*data)->ox = ((*data)->ox_mod * M_PI) / 180;
    (*data)->oy = ((*data)->oy_mod * M_PI) / 180;
    tmp = (*data)->head;
    while (tmp->next != NULL)
    {
        if (tmp->y != tmp->next->y){
            tmp = tmp->next;
            break ;
        }
        tmp = tmp->next;
    }
    (*data)->tmp_vert = tmp;
    tmp = tmp->next;
    while (tmp->next != NULL)
    {
        if (tmp->y != tmp->next->y){
            tmp = tmp->next;
            break ;
        }
        tmp = tmp->next;
    }
    (*data)->tmp_vert_col = tmp;
    draw(&(*data));
}

int key_s(int keycode, t_data **data)
{
    if (keycode == 99)
        (*data)->oy_mod += 10;
    if (keycode == 118)
        (*data)->oy_mod -= 10;
    if (keycode == 98)
        (*data)->ox_mod += 10;
    if (keycode == 110)
        (*data)->ox_mod -= 10;
    if (keycode == 61)
        (*data)->len += 1;
    if (keycode == 45)
        (*data)->len -= 1;
    mlx_clear_window((*data)->mlx,(*data)->win);
    data_reload(&(*data));
    return (0);
}

int key_f(int keycode, t_data **data)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 65363)
        (*data)->x_pox += 10;
    if (keycode == 65361)
        (*data)->x_pox -= 10;
    if (keycode == 65364)
        (*data)->y_pox += 10;
    if (keycode == 65362)
        (*data)->y_pox -= 10;
    if (keycode == 65451)
        ss(&(*data)->head, +1);
    if (keycode == 65453)
        ss(&(*data)->head, -1);
    if (keycode == 122)
        (*data)->oz_mod += 10;
    if (keycode == 120)
        (*data)->oz_mod -= 10;
    key_s(keycode, &(*data));
    mlx_clear_window((*data)->mlx,(*data)->win);
    data_reload(&(*data));
    return (0);
}

void	draw_line(t_data **data, int i)
{
    double dx;
    double dy;
    double x;
    double y;
    double temp;

    x = (*data)->x_home;
    y = (*data)->y_home;
    if (i) {
        dx = (*data)->x_offset - (*data)->x_home;
        dy = (*data)->y_offset - (*data)->y_home;
    }else
    {
        dx = (*data)->x_offset_vert - (*data)->x_home;
        dy = (*data)->y_offset_vert - (*data)->y_home;
    }
    temp = sqrt((dx * dx) + (dy * dy));
    dx /= temp;
    dy /= temp;
    while (temp >= 0)
    {
        ft_put_px(&(*data), (int)y, (int)x, i);
        x += dx;
        y += dy;
        temp--;
    }
}
void draw(t_data **data)
{
	ft_create_image(&(*data), 1);
	while ((*data)->tmp->next != NULL)
	{
		rot_matrix(&(*data));
        (*data)->x_offset = (*data)->x_offset * (*data)->len + (*data)->x_pox;
        (*data)->x_home = (*data)->x_home * (*data)->len + (*data)->x_pox;
        (*data)->y_home = (*data)->y_home * (*data)->len + (*data)->y_pox;
        (*data)->y_offset = (*data)->y_offset * (*data)->len + (*data)->y_pox;
        (*data)->y_offset_vert = (*data)->y_offset_vert * (*data)->len + (*data)->y_pox;
        (*data)->x_offset_vert = (*data)->x_offset_vert * (*data)->len + (*data)->x_pox;
		if ((*data)->tmp->y == (*data)->tmp->next->y) {
			draw_line(&(*data), 1);
		}
        if ((*data)->tmp_vert->next != NULL) {
	        draw_line(&(*data), 0);
            (*data)->tmp_vert = (*data)->tmp_vert->next;
        }
        (*data)->tmp = (*data)->tmp->next;
	}
	ft_create_image(&(*data), 2);
}

void mlx_it(t_data **data)
{
    (*data)->mlx = mlx_init();
    (*data)->win = mlx_new_window((*data)->mlx, 1280, 720, "FDF");
    (*data)->x_pox = 0;
    (*data)->y_pox = 0;
    (*data)->height = 1;
	(*data)->img_size_x = 1280;
	(*data)->img_size_y = 720;
    (*data)->oz_mod = 0;
    (*data)->ox_mod = 0;
    (*data)->len = 1;
    (*data)->oy_mod = 0;
    data_reload(&(*data));
}

int		loop_event(t_data **data)
{
    data_reload(&(*data));
    return (0);
}

int main(int argc, char **argv)
{
	int fd;
	t_data *data;
	if (argc > 1)
	{
		fd = open(argv[1],O_RDONLY);
		if (fd < 0)
			return (0);
		data = coord_read(fd);
        mlx_it(&data);
        mlx_hook(data->win, 2, 3, key_f, &data);
        mlx_loop_hook(data->mlx, &loop_event, &data);
        mlx_loop(data->mlx);
	}
	return (0);
}
/*
#include "fdf.h"

void ss(t_coord **tmp, int i)
{
	t_coord *sub;

	sub = (*tmp);
	while ((*tmp)->next != NULL)
	{
		if ((*tmp)->z > 1 && i == -1)
			(*tmp)->z += i;
		else if ((*tmp)->z > 0 && i != -1 )
			(*tmp)->z += i;
		(*tmp) = (*tmp)->next;
	}
	(*tmp) = sub;
}

void rot_matrix(t_data **data)
{
	(*data)->x_home = (((*data)->center_x + ((*data)->tmp->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp->y - (*data)->center_y) * sin((*data)->oz)));
	(*data)->y_home = (((*data)->center_y + ((*data)->tmp->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp->x - (*data)->center_x) * sin((*data)->oz)));
	(*data)->x_offset = (((*data)->center_x + ((*data)->tmp->next->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp->next->y - (*data)->center_y) * sin((*data)->oz)));
	(*data)->y_offset = (((*data)->center_y + ((*data)->tmp->next->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp->next->x - (*data)->center_x) * sin((*data)->oz)));
	(*data)->x_home = (((*data)->center_x + ((*data)->x_home - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp->z * sin((*data)->oy)));
	(*data)->x_offset = (((*data)->center_x + ((*data)->x_offset - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp->next->z * sin((*data)->oy)));
	(*data)->y_home = (((*data)->center_y + ((*data)->y_home - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp->z * sin((*data)->ox)));
	(*data)->y_offset = (((*data)->center_y + ((*data)->y_offset - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp->next->z * sin((*data)->ox)));
	(*data)->x_offset_vert = (((*data)->center_x + ((*data)->tmp_vert->x - (*data)->center_x) * cos((*data)->oz)) - (((*data)->tmp_vert->y - (*data)->center_y) * sin((*data)->oz)));
	(*data)->y_offset_vert = (((*data)->center_y + ((*data)->tmp_vert->y - (*data)->center_y) * cos((*data)->oz)) + (((*data)->tmp_vert->x - (*data)->center_x) * sin((*data)->oz)));
	(*data)->x_offset_vert = (((*data)->center_x + ((*data)->x_offset_vert - (*data)->center_x) * cos((*data)->oy)) + ((*data)->tmp_vert->z * sin((*data)->oy)));
	(*data)->y_offset_vert = (((*data)->center_y + ((*data)->y_offset_vert - (*data)->center_y) * cos((*data)->ox)) + ((*data)->tmp_vert->z * sin((*data)->ox)));
}


void line(t_data **data, int fl)
{
	int x1,x2,y1,y2;
	x1 = (int)(*data)->x_home;
	y1 = (int)(*data)->y_home;
	if (fl)
	{
		x2 = (int)(*data)->x_offset;
		y2 = (int)(*data)->y_offset;
	}else
	{
		x2 = (int)(*data)->x_offset_vert;
		y2 = (int)(*data)->y_offset_vert;
	}
	int dy = y2 - y1;
	int dx = x2 - x1;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
	dy <<= 1;
	dx <<= 1;

	mlx_pixel_put((*data)->mlx,(*data)->win,x1,y1,0x00FFFFFF);
	if (dx > dy)
	{
		int fraction = dy - (dx >> 1);
		while (x1 != x2)
		{
			if (fraction >= 0)
			{
				y1 += stepy;
				fraction -= dx;
			}
			x1 += stepx;
			fraction += dy;
			mlx_pixel_put((*data)->mlx,(*data)->win,x1,y1,0x00FFFFFF);
		}
	} else {
		int fraction = dx - (dy >> 1);
		while (y1 != y2) {
			if (fraction >= 0) {
				x1 += stepx;
				fraction -= dy;
			}
			y1 += stepy;
			fraction += dx;
			mlx_pixel_put((*data)->mlx,(*data)->win,x1,y1,0x00FFFFFF);
		}
	}
}

int key_s(int keycode, t_data **data)
{
	if (keycode == 99)
		(*data)->oy_mod += 10;
	if (keycode == 118)
		(*data)->oy_mod -= 10;
	if (keycode == 98)
		(*data)->ox_mod += 10;
	if (keycode == 110)
		(*data)->ox_mod -= 10;
	if (keycode == 61)
		(*data)->len += 1;
	if (keycode == 45)
		(*data)->len -= 1;
	mlx_clear_window((*data)->mlx,(*data)->win);
	data_reload(&(*data));
	return (0);
}

int key_f(int keycode, t_data **data)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 65363)
		(*data)->x_pox += 10;
	if (keycode == 65361)
		(*data)->x_pox -= 10;
	if (keycode == 65364)
		(*data)->y_pox += 10;
	if (keycode == 65362)
		(*data)->y_pox -= 10;
	if (keycode == 65451)
		ss(&(*data)->head, +1);
	if (keycode == 65453)
		ss(&(*data)->head, -1);
	if (keycode == 122)
		(*data)->oz_mod += 10;
	if (keycode == 120)
		(*data)->oz_mod -= 10;
	key_s(keycode, &(*data));
	mlx_clear_window((*data)->mlx,(*data)->win);
	data_reload(&(*data));
	return (0);
}

void data_reload(t_data **data)
{
	t_coord *tmp;
	(*data)->tmp = (*data)->head;
	(*data)->oz = ((*data)->oz_mod * M_PI) / 180;
	(*data)->ox = ((*data)->ox_mod * M_PI) / 180;
	(*data)->oy = ((*data)->oy_mod * M_PI) / 180;
	tmp = (*data)->head;
	while (tmp->next != NULL)
	{
		if (tmp->y != tmp->next->y){
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
	(*data)->tmp_vert = tmp;
	draw(&(*data));
}

void draw(t_data **data)
{
	while ((*data)->tmp->next != NULL)
	{
		rot_matrix(&(*data));
		(*data)->x_offset = (*data)->x_offset * (*data)->len + (*data)->x_pox;
		(*data)->x_home = (*data)->x_home * (*data)->len + (*data)->x_pox;
		(*data)->y_home = (*data)->y_home * (*data)->len + (*data)->y_pox;
		(*data)->y_offset = (*data)->y_offset * (*data)->len + (*data)->y_pox;
		(*data)->y_offset_vert = (*data)->y_offset_vert * (*data)->len + (*data)->y_pox;
		(*data)->x_offset_vert = (*data)->x_offset_vert * (*data)->len + (*data)->x_pox;
		if ((*data)->tmp->y == (*data)->tmp->next->y) {
			line(&(*data), 1);
		}
		if ((*data)->tmp_vert->next != NULL) {
			line(&(*data), 0);
			(*data)->tmp_vert = (*data)->tmp_vert->next;
		}
		(*data)->tmp = (*data)->tmp->next;
	}
	mlx_key_hook((*data)->win, key_f, &(*data));
	mlx_loop((*data)->mlx);
}

void mlx_it(t_data **data)
{
	(*data)->mlx = mlx_init();
	(*data)->win = mlx_new_window((*data)->mlx, 1920, 1080, "FDF");
	(*data)->x_pox = 0;
	(*data)->y_pox = 0;
	(*data)->height = 1;
	(*data)->oz_mod = 0;
	(*data)->ox_mod = 0;
	(*data)->len = 1;
	(*data)->oy_mod = 0;
	data_reload(&(*data));
}

int main(int argc, char **argv)
{
	int fd;
	t_data *data;
	if (argc > 1)
	{
		fd = open(argv[1],O_RDONLY);
		if (fd < 0)
			return (0);
		data = coord_read(fd);
		mlx_it(&data);
	}
	return (0);
}*/

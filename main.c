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

void line(int x1, int x2, int y1 ,int y2, void *mlx, void *wnd)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;        // dy is now 2*dy
    dx <<= 1;        // dx is now 2*dx

    mlx_pixel_put(mlx,wnd,x1,y1,0x00FFFFFF);
    if (dx > dy)
    {
        int fraction = dy - (dx >> 1);  // same as 2*dy - dx
        while (x1 != x2)
        {
            if (fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;          // same as fraction -= 2*dx
            }
            x1 += stepx;
            fraction += dy;              // same as fraction -= 2*dy
            mlx_pixel_put(mlx,wnd,x1,y1,0x00FFFFFF);
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
            mlx_pixel_put(mlx,wnd,x1,y1,0x00FFFFFF);
        }
    }
}
void lines(int x1, int x2, int y1 ,int y2, void *mlx, void *wnd)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;        // dy is now 2*dy
    dx <<= 1;        // dx is now 2*dx

    mlx_pixel_put(mlx,wnd,x1,y1,0x00FF88FF);
    if (dx > dy)
    {
        int fraction = dy - (dx >> 1);  // same as 2*dy - dx
        while (x1 != x2)
        {
            if (fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;          // same as fraction -= 2*dx
            }
            x1 += stepx;
            fraction += dy;              // same as fraction -= 2*dy
            mlx_pixel_put(mlx,wnd,x1,y1,0x00FF88FF);
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
            mlx_pixel_put(mlx,wnd,x1,y1,0x00FF88FF);
        }
    }
}
void draw(t_coord *head)
{
	double y;
	double x;
    double x1;
    double y1;
	int len;
    int flag;
	int pos;
	int window;
	void *mlx;
	void *img;
	void *wnd;
	char *str;
	t_coord *tmp;

	mlx = mlx_init();
	window = 1000;
	wnd = mlx_new_window(mlx, window, window, "FDF");
	len = 20;
	pos = 200;
    flag = 1;
    tmp = head;
    double oz = M_PI / 8;
    double ox =   - (M_PI / 3);
    double yr;
    double xr;
    double z;
    double yr1;
    double z1;
    double xr1;
	double oy =   - (M_PI / 6);
	double center_y = 11 / 2;
	double center_x = 19 / 2;
	while (head->next != NULL)
	{

		x = center_x + (head->x - center_x) * cos(oz) - (head->y - center_y) * sin(oz); // OZ
		y = center_y + (head->y - center_y) * cos(oz) + (head->x - center_x) * sin(oz); // OZ

		x1 = center_x + (head->next->x - center_x) * cos(oz) - (head->next->y - center_y) * sin(oz); // OZ
		y1 = center_y + (head->next->y - center_y) * cos(oz) + (head->next->x - center_x) * sin(oz); // OZ

		x  = center_x + (x - center_x) * cos(oy) + head->z * sin(oy); // OY
		x1 = center_x + (x1 - center_x) * cos(oy) + head->next->z * sin(oy);// OY


		y = center_y + (y - center_y) * cos(ox) + head->z*sin(ox) ; // OX
		y1 = center_y + (y1 - center_y) * cos(ox) + head->next->z*sin(ox) ; // OX

        while (tmp->next != NULL && flag == 1)
        {
            if (tmp->y != tmp->next->y){
                tmp = tmp->next;
                flag = 0;
                break ;
            }
            tmp = tmp->next;
        }
		if (head->y == head->next->y) {
            line(x * len + pos, x1 * len + pos, y * len + pos, y1 * len + pos, mlx, wnd);
        }

		x1 = center_x + (tmp->x - center_x) * cos(oz) - (tmp->y - center_y) * sin(oz); // OZ
		y1 = center_y + (tmp->y - center_y) * cos(oz) + (tmp->x - center_x) * sin(oz); // OZ

		x1 = center_x + (x1 - center_x) * cos(oy) + tmp->z * sin(oy); // OY
		y1 = center_y + (y1 - center_y) * cos(ox) + tmp->z*sin(ox) ; // OX

        if (tmp->next != NULL) {
            line(x * len + pos, x1 * len + pos, y * len + pos, y1 * len + pos, mlx, wnd);
            tmp = tmp->next;
        }
		head = head->next;
	}
	mlx_loop(mlx);
}

int main(int argc, char **argv)
{
	int fd;
	t_coord *head;

	if (argc > 1)
	{
		fd = open(argv[1],O_RDONLY);
		if (fd < 0)
			return (0);
		head = coord_read(fd);
        draw(head);
	}
	return (0);
}
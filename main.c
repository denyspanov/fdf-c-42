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


void line(double x1, double x2, double y1, double y2, void *mlx, void *wnd)
{
	double dx = fabs(x2 - x1), sx = x1<x2 ? 1 : -1;
	double dy = fabs(y2 - y1), sy = y1<y2 ? 1 : -1;
	double err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		mlx_pixel_put(mlx, wnd, x1, y1, 0x004055FF);
		if (x1==x2 && y1==y2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
}

void draw(t_coord *head)
{
	double y;
	double x;
	int len;
	int pos;
	int window;
	void *mlx;
	void *img;
	void *wnd;
	char *str;
	int g;
	char *data;
	int		bits_per_pix;
	int		linesize;
	int		endian;

	mlx = mlx_init();
	window = 1000;
	wnd = mlx_new_window(mlx, window, window, "FDF");
	img = mlx_new_image(mlx, 100, 100);
	data = mlx_get_data_addr(img, &bits_per_pix, &linesize, &endian);
	len = 20;
	pos = 100;
	g = 60;
	while (head->next != NULL)
	{
		line(head->x * len + pos, head->next->x * len + pos, head->y * len + pos, head->y * len + pos, mlx, wnd);
		line(head->x * len + pos, head->x * len + pos, head->y * len + pos, head->next->y + 1 * len + pos, mlx, wnd);
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
		while (head->next != NULL)
		{
			printf("x: %f ", head->x);
			printf("y: %f ", head->y);
			printf("z: %f \n", head->z);
			head = head->next;
		}
	}
	return (0);
}
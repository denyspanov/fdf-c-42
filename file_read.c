/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:36 by dpanov            #+#    #+#             */
/*   Updated: 2017/02/28 16:24:36 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void line_draw(float x1, float x2, float y1, float y2, void *mlx, void *wnd)
{
	double dx, dy, p, end;
	float x, y;
	dx = fabs(x1 - x2);
	dy = fabs(y1 - y2);
	p = 2 * dy - dx;
	if(x1 > x2)
	{
		x = x2;
		y = y2;
		end = x1;
	}
	else
	{
		x = x1;
		y = y1;
		end = x2;
	}
	mlx_pixel_put(mlx, wnd, x, y, 0x00FFFFFF);
	while(x < end)
	{
		x = x + 1;
		if(p < 0)
		{
			p = p + 2 * dy;
		}
		else
		{
			y = y + 1;
			p = p + 2 * (dy - dx);
		}
		mlx_pixel_put(mlx, wnd, x, y, 0x00FFFFFF);
	}
}

void draw(t_mas **mas)
{
	int y;
	int x;
	void *mlx;
	void *wnd;
	int counter;

	counter = 20;
	mlx = mlx_init();
	wnd = mlx_new_window(mlx, 1000, 1000, "FDF");
	y = -1;
	while (++y < (*mas)->y)
	{
		x = -1;
		while (++x < (*mas)->x)
		{
			line_draw((*mas)->mas[y][x] + x *counter + 100,(*mas)->mas[y][x] + x * counter + 200, (*mas)->mas[y][x] + y * counter + 100,(*mas)->mas[y][x] + y * counter + 100, mlx, wnd);
			counter = 20;
		}
		line_draw((*mas)->mas[y][x] + x *counter + 100,(*mas)->mas[y][x] + x * counter + 100, (*mas)->mas[y][x] + y * counter + 200,(*mas)->mas[y][x] + y * counter + 200, mlx, wnd);
	}
	mlx_loop(mlx);
}

int mas_create(int fd)
{
	int i;
	int j;
	int x;
	char *line;
	char *temp;
	t_mas *mas;

	mas = (t_mas *)malloc(sizeof(t_mas));
	mas->mas = (int **)malloc(sizeof(int **));
	mas->y= 0;
	mas->x = 0;
	while ((get_next_line(fd,&line))> 0)
	{
		mas->mas[mas->y] = (int *)malloc(sizeof(int *));
		i = -1;
		x = 0;
		while (line[++i])
		{
			if (line[i] > 47 && line[i] < 58)
			{
				j = i;
				while (line[i] > 47 && line[i] < 58)
					i++;
				temp = ft_strsub(line, j, i - j);
				mas->mas[mas->y][x] = ft_atoi(temp);
				x++;
				mas->x++;
			}
		}
		mas->y++;
	}
	mas->x /= mas->y;
	draw(&mas);
	return (0);
}


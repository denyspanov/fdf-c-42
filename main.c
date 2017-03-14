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

void draw(t_mas **data)
{
	int y;
	int x;
	void *mlx;
	void *wnd;
	int counter;

	counter = 10;
	mlx = mlx_init();
	wnd = mlx_new_window(mlx, 2000, 2000, "FDF");
	y = -1;
	while (++y < (*data)->y)
	{
		x = -1;
		counter = 10;
		while (++x < (*data)->x)
		{
			if (x + 1 != (*data)->x)
				line_draw((*data)->mas[y][x] + counter, (*data)->mas[y][x] + counter,(*data)->mas[y][x] + y * 10,(*data)->mas[y][x] + y * 10,mlx, wnd);
			counter += 10;
		}
	}
	mlx_loop(mlx);
}

int main(int argc, char **argv)
{
	int fd;
	t_mas *data;
	int i;
	int j;

	if (argc > 1)
	{
		fd = open(argv[1],O_RDONLY);
		if (fd < 0)
			return (0);
		data = mas_create(fd, argv[1]);
		draw(&data);
		/*j = -1;
		while (++j < data->y)
		{
			i = -1;
			while (++i < data->x)
			{
				printf("%d  ",data->mas[j][i]);
			}
			printf("\n");
		}*/
	}
	return (0);
}
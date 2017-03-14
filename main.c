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

void line(t_mas **data)
{
	double dx = abs((int)(*data)->x2 - (int)(*data)->x1), sx = (*data)->x1<(*data)->x2 ? 1 : -1;
	double dy = abs((int)(*data)->y2 - (int)(*data)->y1), sy = (*data)->y1<(*data)->y2 ? 1 : -1;
	double err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		mlx_pixel_put((*data)->mlx, (*data)->wnd, (int)(*data)->x1, (int)(*data)->y1, 0x004055FF);
		if ((*data)->x1==(*data)->x2 && (*data)->y1==(*data)->y2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; (*data)->x1 += sx; }
		if (e2 < dy) { err += dx; (*data)->y1 += sy; }
	}
}

void draw(t_mas **data)
{
	int y;
	int x;
	int len;
	int pos;
	double L;
	double B;
	double F;

	(*data)->mlx = mlx_init();
	(*data)->wnd = mlx_new_window((*data)->mlx, 2000, 2000, "FDF");
	y = -1;
	len = 20;
	pos = 100;
	while (++y < (*data)->y)
	{
		x = -1;
		(*data)->x1 = -(*data)->mas[y][0] + pos;
		(*data)->y1 = -(*data)->mas[y][0] + pos + y * len;
		L = sqrt(((*data)->x1 * (*data)->x1) + ((*data)->y1 * (*data)->y1) - (2 * ((*data)->x1 * (*data)->y1) * cos(60)));
		B = acos(((((*data)->x1 * (*data)->x1) + (L * L)) - ((*data)->y1 * (*data)->y1)) / (2 * ((*data)->x1) * L));
		F = 60 + B;
		(*data)->x1 = L * cos(F);
		(*data)->x1 = L * sin(F) + (*data)->mas[y][x];
		while (++x < (*data)->x)
		{
			if (x + 1 != (*data)->x)
			{
				(*data)->x2 = len * (x + 1) - (*data)->mas[y][x + 1] + pos;
				(*data)->y2 = len * y - (*data)->mas[y][x + 1] + pos;
				L = sqrt(((*data)->x2 * (*data)->x2) + ((*data)->y2 * (*data)->y2) - (2 * ((*data)->x2 * (*data)->y2) * cos(60)));
				B = acos(((((*data)->x2 * (*data)->x2) + (L * L)) - ((*data)->y2 * (*data)->y2)) / (2 * ((*data)->x2) * L));
				F = L + B;
				(*data)->x2 = L * cos(F);
				(*data)->y2 = L * sin(F) + (*data)->mas[y][x];
				line(&(*data));
				(*data)->x1 = (*data)->x2;
			}
		}
	}
	/*y = -1;
	while (++y < (*data)->y - 1)
	{
		x = -1;
		while (++x < (*data)->x)
		{
			(*data)->x1 = len * x - (*data)->mas[y][x] + pos;
			(*data)->x2 = len * x - (*data)->mas[y + 1][x] + pos;
			(*data)->y1 = len * y - (*data)->mas[y][x] + pos;
			(*data)->y2 = len * (y + 1) - (*data)->mas[y + 1][x] + pos;

			line(&(*data));
		}
	}*/
	mlx_loop((*data)->mlx);
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
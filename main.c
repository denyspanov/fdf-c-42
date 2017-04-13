/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:43 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/25 13:16:33 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_s(int keycode, t_data **data)
{
	if (keycode == KEY_X)
		(*data)->oy_mod += 10;
	if (keycode == KEY_S)
		(*data)->oy_mod -= 10;
	if (keycode == KEY_C)
		(*data)->ox_mod += 10;
	if (keycode == KEY_D)
		(*data)->ox_mod -= 10;
	if (keycode == KEY_EQUAL)
		(*data)->len += 1;
	if (keycode == KEY_MINUS && (*data)->len > 1)
		(*data)->len -= 1;
	if (keycode == KEY_R && (*data)->bas_r < 255)
		(*data)->bas_r++;
	if (keycode == KEY_T && (*data)->bas_r > 1)
		(*data)->bas_r--;
	if (keycode == KEY_G && (*data)->bas_g < 255)
		(*data)->bas_g++;
	if (keycode == KEY_H && (*data)->bas_g > 1)
		(*data)->bas_g--;
	mlx_clear_window((*data)->mlx, (*data)->win);
	data_reload(&(*data));
	return (0);
}

void	rot_matri_y(t_data **data)
{
	double x;
	double z;

	x = (*data)->x_home;
	z = (*data)->z_home;
	(*data)->x_home = ((*data)->center_x + (x - (*data)->center_x)
				* cos((*data)->oy) - z * sin((*data)->oy));
	(*data)->z_home = z * cos((*data)->oy) + x * sin((*data)->oy);
	x = (*data)->x_offset;
	z = (*data)->z_offset;
	(*data)->x_offset = ((*data)->center_x + (x - (*data)->center_x)
				* cos((*data)->oy) - z * sin((*data)->oy));
	(*data)->z_offset = z * cos((*data)->oy) + x * sin((*data)->oy);
	x = (*data)->x_offset_vert;
	z = (*data)->z_vert;
	(*data)->x_offset_vert = ((*data)->center_x + (x - (*data)->center_x)
				* cos((*data)->oy) - z * sin((*data)->oy));
	(*data)->z_vert = z * cos((*data)->oy) + x * sin((*data)->oy);
}

int		key_f(int keycode, t_data **data)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	if (keycode == KEY_RIGHT)
		(*data)->x_pox += 10;
	if (keycode == KEY_LEFT)
		(*data)->x_pox -= 10;
	if (keycode == KEY_DOWN)
		(*data)->y_pox += 10;
	if (keycode == KEY_UP)
		(*data)->y_pox -= 10;
	if (keycode == KEY_PAD_ADD)
		ss(&(*data), +1);
	if (keycode == KEY_PAD_SUB)
		ss(&(*data), -1);
	if (keycode == KEY_Z)
		(*data)->oz_mod += 10;
	if (keycode == KEY_A)
		(*data)->oz_mod -= 10;
	if (keycode == KEY_B && (*data)->bas_b < 255)
		(*data)->bas_b++;
	if (keycode == KEY_N && (*data)->bas_b > 1)
		(*data)->bas_b--;
	key_s(keycode, &(*data));
	return (0);
}

int		loop_event(t_data **data)
{
	data_reload(&(*data));
	display_menu(&(*data));
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_data	*data;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (0);
		data = coord_read(fd);
		mlx_it(&data);
		mlx_hook(data->win, 2, 3, key_f, &data);
		mlx_loop_hook(data->mlx, &loop_event, &data);
		mlx_loop(data->mlx);
	}
	else
	{
		ft_putstr("Usage: ./fdf [map]\n");
	}
	return (0);
}

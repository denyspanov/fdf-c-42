/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:32:00 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/24 16:00:09 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_it(t_data **data)
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
	(*data)->height = 1;
	(*data)->oy_mod = 0;
	(*data)->bas_b = 100;
	(*data)->bas_g = 100;
	(*data)->bas_r = 100;
	data_reload(&(*data));
}

void	data_reload(t_data **data)
{
	t_coord *tmp;

	(*data)->tmp = (*data)->head;
	(*data)->oz = ((*data)->oz_mod * M_PI) / 180;
	(*data)->ox = ((*data)->ox_mod * M_PI) / 180;
	(*data)->oy = ((*data)->oy_mod * M_PI) / 180;
	tmp = (*data)->head;
	while (tmp->next != NULL)
	{
		if (tmp->y != tmp->next->y)
		{
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
	(*data)->tmp_vert = tmp;
	draw(&(*data));
}

void	ft_create_image(t_data **data, int n)
{
	int		sizeline;
	int		endian;
	int		bpp;

	if (n == 1)
	{
		(*data)->img = mlx_new_image((*data)->mlx,
								(*data)->img_size_x, (*data)->img_size_y);
		(*data)->data = mlx_get_data_addr((*data)->img,
								&bpp, &sizeline, &endian);
	}
	if (n == 2)
	{
		mlx_put_image_to_window((*data)->mlx, (*data)->win, (*data)->img, 0, 0);
		mlx_destroy_image((*data)->mlx, (*data)->img);
	}
}

void	display_menu(t_data **data)
{
	mlx_string_put((*data)->mlx, (*data)->win, 20, 10, 0xFFFFFF,
				"Numpad(+,-): change height.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 24, 0xFFFFFF,
				"(A,Z): change oz.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 39, 0xFFFFFF,
				"(S,X): change ox.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 53, 0xFFFFFF,
				"(D,C): change oy.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 67, 0xFFFFFF,
				"(-,+): change zoom.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 123, 0xFFFFFF,
				"Arrows: change position.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 80, 0xFFFFFF,
				"(R,T): color change R.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 94, 0xFFFFFF,
				"(G,H): color change G.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 109, 0xFFFFFF,
				"(B,N): color change B.");
	mlx_string_put((*data)->mlx, (*data)->win, 20, 137, 0xFFFFFF,
				"Esc: exit.");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:45:29 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/25 13:19:08 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_px(t_data **data, int y, int x, int i)
{
	int p;

	p = (x * 4) + (y * 5120);
	if (p >= 0 && p < (3686400) && x < 1280 && y < 720 && x > 0)
	{
		(*data)->data[p] = (*data)->bas_b;
		(*data)->data[p + 1] = (*data)->bas_g;
		(*data)->data[p + 2] = (*data)->bas_r;
		if ((*data)->tmp->color && i == 1)
		{
			(*data)->data[p] = (*data)->tmp->b;
			(*data)->data[p + 1] = (*data)->tmp->g;
			(*data)->data[p + 2] = (*data)->tmp->r;
		}
		else if (((*data)->tmp_vert->color))
		{
			(*data)->data[p] = (*data)->tmp_vert->b;
			(*data)->data[p + 1] = (*data)->tmp_vert->g;
			(*data)->data[p + 2] = (*data)->tmp_vert->r;
		}
	}
}

void	draw_line(t_data **data, int c)
{
	double i[5];

	i[0] = (*data)->x_home;
	i[1] = (*data)->y_home;
	if (c)
	{
		i[3] = (*data)->x_offset - (*data)->x_home;
		i[4] = (*data)->y_offset - (*data)->y_home;
	}
	else
	{
		i[3] = (*data)->x_offset_vert - (*data)->x_home;
		i[4] = (*data)->y_offset_vert - (*data)->y_home;
	}
	i[2] = sqrt((i[3] * i[3]) + (i[4] * i[4]));
	i[3] /= i[2];
	i[4] /= i[2];
	while (i[2] >= 0)
	{
		ft_put_px(&(*data), (int)i[1], (int)i[0], c);
		i[0] += i[3];
		i[1] += i[4];
		i[2]--;
	}
}

void	draw(t_data **data)
{
	ft_create_image(&(*data), 1);
	while ((*data)->tmp->next != NULL)
	{
		rot_matrix(&(*data));
		(*data)->x_offset = (*data)->x_offset * (*data)->len + (*data)->x_pox;
		(*data)->x_home = (*data)->x_home * (*data)->len + (*data)->x_pox;
		(*data)->y_home = (*data)->y_home * (*data)->len + (*data)->y_pox;
		(*data)->y_offset = (*data)->y_offset * (*data)->len + (*data)->y_pox;
		(*data)->y_offset_vert = ((*data)->y_offset_vert
						* (*data)->len + (*data)->y_pox);
		(*data)->x_offset_vert = ((*data)->x_offset_vert
						* (*data)->len + (*data)->x_pox);
		if ((*data)->tmp->y == (*data)->tmp->next->y)
			draw_line(&(*data), 1);
		if ((*data)->tmp_vert->next != NULL)
		{
			draw_line(&(*data), 0);
			(*data)->tmp_vert = (*data)->tmp_vert->next;
		}
		(*data)->tmp = (*data)->tmp->next;
	}
	ft_create_image(&(*data), 2);
}

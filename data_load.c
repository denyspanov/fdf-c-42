/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:34:39 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/25 13:14:25 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_matri_x(t_data **data)
{
	double y;
	double z;

	y = (*data)->y_home;
	z = (*data)->tmp->z * (*data)->height;
	(*data)->y_home = ((*data)->center_y + (y - (*data)->center_y)
				* cos((*data)->ox) + z * sin((*data)->ox));
	(*data)->z_home = z * cos((*data)->ox) - y * sin((*data)->ox);
	y = (*data)->y_offset;
	z = (*data)->tmp->next->z * (*data)->height;
	(*data)->y_offset = ((*data)->center_y + (y - (*data)->center_y)
				* cos((*data)->ox) + z * sin((*data)->ox));
	(*data)->z_offset = z * cos((*data)->ox) - y * sin((*data)->ox);
	y = (*data)->y_offset_vert;
	z = (*data)->tmp_vert->z * (*data)->height;
	(*data)->y_offset_vert = ((*data)->center_y + (y - (*data)->center_y)
						* cos((*data)->ox) + z * sin((*data)->ox));
	(*data)->z_vert = z * cos((*data)->ox) - y * sin((*data)->ox);
	rot_matri_y(&(*data));
}

void	rot_matrix(t_data **data)
{
	double x;
	double y;

	x = (*data)->tmp->x;
	y = (*data)->tmp->y;
	(*data)->x_home = ((*data)->center_x + (x - (*data)->center_x)
		* cos((*data)->oz) + (y - (*data)->center_y) * sin((*data)->oz));
	(*data)->y_home = ((*data)->center_y + (y - (*data)->center_y)
		* cos((*data)->oz) - (x - (*data)->center_x) * sin((*data)->oz));
	x = (*data)->tmp->next->x;
	y = (*data)->tmp->next->y;
	(*data)->x_offset = ((*data)->center_x + (x - (*data)->center_x)
		* cos((*data)->oz) + (y - (*data)->center_y) * sin((*data)->oz));
	(*data)->y_offset = ((*data)->center_y + (y - (*data)->center_y)
		* cos((*data)->oz) - (x - (*data)->center_x) * sin((*data)->oz));
	x = (*data)->tmp_vert->x;
	y = (*data)->tmp_vert->y;
	(*data)->x_offset_vert = ((*data)->center_x + (x - (*data)->center_x)
		* cos((*data)->oz) + (y - (*data)->center_y) * sin((*data)->oz));
	(*data)->y_offset_vert = ((*data)->center_y + (y - (*data)->center_y)
		* cos((*data)->oz) - (x - (*data)->center_x) * sin((*data)->oz));
	rot_matri_x(&(*data));
}

void	ss(t_data **data, int i)
{
	if (i == 1)
	{
		(*data)->height += 0.1;
	}
	else
	{
		(*data)->height -= 0.1;
	}
}

void	val_string_s(char *s, int i)
{
	int flag;
	int j;

	flag = 0;
	j = -1;
	if (s[i])
	{
		if (s[i] != '0' || s[i + 1] != 'x')
			flag = 1;
		i += 2;
		while (++j < 6 && s[++i])
			if (!((s[i] > 47 && s[i] < 58) || (s[i] > 64 && s[i] < 71)
			|| (s[i] > 96 && s[i] < 103)))
				flag = 1;
	}
	if (s[i])
		flag = 1;
	if (flag)
	{
		ft_putstr("File error: invalid data.\n");
		exit(0);
	}
}

void	val_string(char *s)
{
	int i;

	i = 0;
	if (s[0] == '-')
		i++;
	while (s[i] > 47 && s[i] < 58 && s[i])
		i++;
	if (s[i] == ',')
		i++;
	val_string_s(s, i);
}

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

t_mas     *mas_size(int fd, t_mas **data)
{
	char *line;
	int i;

	(*data)->y = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		i = 0;
		(*data)->x = 1;
		while (line[i++] != '\0')
		{
			if (line[i] > 47 && line[i] < 58)
			{
				while (line[i] > 47 && line[i] < 58)
					i++;
				(*data)->x++;
			}
		}
		(*data)->y++;
	}
	return (*data);
}

t_mas *mas_create(int fd, char *src)
{
	int i;
	int j;
	char *line;
	char *temp;
	t_mas *data;

	data = (t_mas *)malloc(sizeof(t_mas));
	data = mas_size(fd, &data);
	close(fd);
	fd = open(src,O_RDONLY);
	data->mas = (int **)malloc(data->y * sizeof(int *));    
	data->y = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		data->mas[data->y] = (int *)malloc(data->x * sizeof(int *));
		i = -1;
		data->x = 0;
		while (line[++i])
		{
			if ((line[i] > 47 && line[i] < 58) || line[i] == '-')
			{
				j = i;
				while ((line[i] > 47 && line[i] < 58) || line[i] == '-')
					i++;
				temp = ft_strsub(line, j, i - j);
				data->mas[data->y][data->x] = ft_atoi(temp);
				data->x++;
			}
		}
		data->y++;
	}
	return (data);
}


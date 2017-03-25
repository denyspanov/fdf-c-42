/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:36 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/24 13:44:32 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_hex(const char *s, t_coord **tmp)
{
	int i;
	int j;
	int mas[6];

	j = 0;
	while (s[j] != 'x' && s[j] != '\0')
		j++;
	i = (int)ft_strlen(s);
	if (j == i)
		return (0);
	i = -1;
	while (s[++j] && ++i < 6)
	{
		if (s[j] > 47 && s[j] < 58)
			mas[i] = (int)s[j] - 48;
		else if (s[j] > 64 && s[j] < 71)
			mas[i] = (int)s[j] - 55;
	}
	(*tmp)->r = 16 * mas[0] + mas[1];
	(*tmp)->g = 16 * mas[2] + mas[3];
	(*tmp)->b = 16 * mas[4] + mas[5];
	return (1);
}

int		coord_put(t_coord **tmp, char **src, int x, int y)
{
	while (src[++x])
	{
		val_string(src[x]);
		(*tmp)->x = x;
		(*tmp)->y = y;
		(*tmp)->z = ft_atoi(src[x]);
		(*tmp)->color = ft_atoi_hex(src[x], &(*tmp));
		(*tmp)->next = (t_coord *)malloc(sizeof(t_coord));
		(*tmp)->next->next = NULL;
		(*tmp) = (*tmp)->next;
	}
	return (x);
}

void	er_handler(t_data **data, int i)
{
	if ((*data)->fl_x == 0 && i == 1)
	{
		(*data)->f_x = (*data)->max_x;
		(*data)->fl_x = 1;
	}
	if ((*data)->f_x != (*data)->max_x && i == 1)
	{
		ft_putstr("File error: (x != x).\n");
		exit(0);
	}
	if ((*data)->max_y == 0 & i == 2)
	{
		ft_putstr("File error: empty.\n");
		exit(0);
	}
}

t_data	*coord_read(int fd)
{
	t_data	*head;
	t_coord	*tmp;
	char	*line;
	char	**str;
	int		i[2];

	if (!(tmp = (t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	if (!(head = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	i[0] = 0;
	head->head = tmp;
	head->fl_x = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		str = ft_strsplit(line, ' ');
		head->max_x = coord_put(&tmp, str, -1, i[0]);
		er_handler(&head, 1);
		i[0]++;
	}
	head->max_y = i[0];
	er_handler(&head, 2);
	head->center_x = head->max_x / 2.0;
	head->center_y = i[0] / 2.0;
	return (head);
}

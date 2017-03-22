/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:36 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/22 16:23:21 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		back_char(const char c)
{
	char *s;

	if (c >= 48 && c <= 57)
	{
		s = ft_strnew(2);
		s[0] = c;
		s[1] = '\0';
		return (ft_atoi(s));
	}
	else if (c == 'a' || c == 'A')
		return (10);
	else if (c == 'b' || c == 'B')
		return (11);
	else if (c == 'c' || c == 'C')
		return (12);
	else if (c == 'd' || c == 'D')
		return (13);
	else if (c == 'e' || c == 'E')
		return (14);
	else if (c == 'f' || c == 'F')
		return (15);
	else
		return (0);
}

int		ft_pow(int number, int power)
{
	int	res;

	if (power == 0)
		return (1);
	res = 1;
	while (power != 0)
	{
		res *= number;
		power--;
	}
	return (res);
}

int		ft_atoi_hex(const char *s)
{
	int n;
	int i;
	int j;

	n = 0;
	j = 0;
	while (s[j] != 'x' && s[j] != '\0')
		j++;
	i = (int)ft_strlen(s);
	if (j == i)
		return (0);
	j = 0;
	while (s[--i] != 'x')
	{
		n += back_char(s[i]) * ft_pow(16, j);
		j++;
	}
	return (n);
}

int		coord_put(t_coord **tmp, char **src, int x, int y)
{
	while (src[++x])
	{
		(*tmp)->x = x;
		(*tmp)->y = y;
		(*tmp)->z = ft_atoi(src[x]);
		(*tmp)->color = ft_atoi_hex(src[x]);
		(*tmp)->next = (t_coord *)malloc(sizeof(t_coord));
		(*tmp)->next->next = NULL;
		(*tmp) = (*tmp)->next;
	}
	return (x);
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
	while ((get_next_line(fd, &line)) > 0)
	{
		str = ft_strsplit(line, ' ');
		head->max_x = coord_put(&tmp, str, -1, i[0]);
		i[0]++;
	}
	head->max_y = i[0];
	head->center_x = head->max_x / 2.0;
	head->center_y = i[0] / 2.0;
	return (head);
}

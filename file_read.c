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

t_coord *coord_read(int fd)
{
	t_coord *head;
	t_coord *tmp;
	char *line;
	char **str;
	int i[2];

	if (!(tmp = (t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	i[0] = 0;
	head = tmp;
	while ((get_next_line(fd, &line)) > 0 )
	{
		i[1] = -1;
		str = ft_strsplit(line, ' ');
		while (str[++i[1]])
		{
			tmp->x = i[1];
			tmp->y = i[0];
			tmp->z = ft_atoi(str[i[1]]);
			tmp->next = (t_coord *)malloc(sizeof(t_coord));
			tmp->next->next = NULL;
			tmp = tmp->next;
		}
		i[0]++;
	}
	return (head);
}


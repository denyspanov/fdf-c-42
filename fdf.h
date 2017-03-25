/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpanov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:57:23 by dpanov            #+#    #+#             */
/*   Updated: 2017/03/25 13:17:09 by dpanov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
	int				color;
	int				r;
	int				g;
	int				b;
	struct s_coord	*next;
}					t_coord;
typedef struct		s_data
{
	struct s_coord	*head;
	struct s_coord	*tmp;
	struct s_coord	*tmp_vert;
	double			center_x;
	double			center_y;
	int				img_size_x;
	int				img_size_y;
	int				max_x;
	int				max_y;
	int				key;
	double			x_home;
	double			y_home;
	double			z_home;
	double			z_offset;
	double			z_vert;
	double			x_offset;
	double			y_offset;
	double			y_offset_vert;
	double			x_offset_vert;
	int				x_pox;
	int				y_pox;
	int				len;
	int				bas_r;
	int				bas_g;
	int				bas_b;
	double			height;
	double			oz;
	double			oz_mod;
	double			ox_mod;
	double			oy_mod;
	double			ox;
	double			oy;
	char			*data;
	void			*mlx;
	void			*win;
	int				f_x;
	int				fl_x;
	void			*img;
}					t_data;
void				rot_matri_y(t_data **data);
void				display_menu(t_data **data);
t_data				*coord_read(int fd);
void				mlx_it(t_data **data);
void				draw(t_data **data);
void				data_reload(t_data **data);
void				rot_matrix(t_data **data);
void				ft_put_px(t_data **data, int y, int x, int i);
void				ft_create_image(t_data **data, int n);
void				ss(t_data **data, int i);
void				val_string(char *s);
#endif

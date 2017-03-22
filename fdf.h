#ifndef _FT_FDF_FT_
# define _FT_FDF_FT_
# include "libft/libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

typedef struct s_coord
{
	double x;
	double y;
	double z;
	int color;
	struct s_coord *next;
}t_coord;
typedef struct s_data
{
	struct s_coord *head;
	struct s_coord *tmp;
	struct s_coord *tmp_vert;
	double center_x;
	double center_y;
	int max_x;
	int max_y;
	double x_home;
	double y_home;
	double x_offset;
	double y_offset;
	double y_offset_vert;
	double x_offset_vert;
	int x_pox;
	int y_pox;
	int len;
	double oz;
	double ox;
	double oy;
	char *data;
	void *mlx;
	void *win;
	void *img;
}t_data;
t_data *coord_read(int fd);
#endif
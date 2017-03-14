#ifndef _FT_FDF_FT_
# define _FT_FDF_FT_
# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

typedef struct s_mas
{
	int **mas;
	int x;
	int y;
	void *mlx;
	void *wnd;
	double x1;
	double x2;
	double y1;
	double y2;
}t_mas;
void draw(t_mas **mas);
t_mas     *mas_size(int fd, t_mas **data);
t_mas *mas_create(int fd, char *src);
#endif
#ifndef _FT_FDF_FT_
# define _FT_FDF_FT_
# include "libft.h"
# include <fcntl.h>
# include "mlx.h"

typedef struct s_mas
{
	int **mas;
	int x;
	int y;
	void *mlx;
	void *wnd;
}t_mas;
int mas_create(int fd);
void draw(t_mas **mas);
void line_draw(float x1, float x2, float y1, float y2, void *mlx, void *wnd);
#endif
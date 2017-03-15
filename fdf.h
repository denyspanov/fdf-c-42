#ifndef _FT_FDF_FT_
# define _FT_FDF_FT_
# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

typedef struct s_coord
{
	double x;
	double y;
	double z;
	unsigned int color;
	struct s_coord *next;
}t_coord;
t_coord *coord_read(int fd);
#endif
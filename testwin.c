#include <mlx.h>

int		main(void)
{
	void *mlx;
	void *win;
	void *img;
	char *data;
	int		bits_per_pix;
	int		linesize;
	int		endian;


	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "test");
	img = mlx_new_image(mlx, 100, 100);
	data = mlx_get_data_addr(img, &bits_per_pix, &linesize, &endian);

	int i = 0;
	int j = 0;
	while (i < 40000)
	{
		data[i] = 255;
		data[i + 1] = 255;
		data[i + 2] = 255;
		data[i + 3] = 0;
		i += 4;
	}
	mlx_put_image_to_window(mlx, win, img, 500, 500);
	mlx_loop(mlx);
	return (0);
}

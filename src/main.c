//42 header goes here

#include "fdf.h"

void	redraw_image(t_info info)
{
	t_v3 **tmp_v3grid;

	tmp_v3grid = copy_v3(info.v3grid, info);
	rotate_x(tmp_v3grid, info, info.xrot);
	rotate_y(tmp_v3grid, info, info.yrot);
	rotate_z(tmp_v3grid, info, info.zrot);
	info.pts = make_pts(info, tmp_v3grid);
	draw(info);
}

void	reset_rot(t_info *info)
{
	info->xrot = 0;
	info->yrot = 0;
	info->zrot = 0;
}

int		key_pressed(int keycode, t_info *info)
{
	float angle;

	angle = M_PI / 96;
	if (keycode == 53)
		exit(0);
	else if (keycode == 13)
		info->xrot += angle;
	else if (keycode == 0)
		info->yrot += angle;
	else if (keycode == 1)
		info->xrot -= angle;
	else if (keycode == 2)
		info->yrot -= angle;
	else if (keycode == 123)
		info->zrot -= angle;
	else if (keycode == 124)
		info->zrot += angle;
	else if (keycode == 15)
		reset_rot(info);
	mlx_clear_window(info->mlx, info->win);
	redraw_image(*info);
	mlx_key_hook(info->win, key_pressed, info);
	return (0);
}

char	*read_file(int fd)
{
	char	*readfile;
	char	tmp[500];
	char	*tmp2;
	int		bytesread;

	bytesread = read(fd, tmp, 500);
	tmp[bytesread] = '\0';
	readfile = ft_strdup(tmp);
	if (!readfile)
		return (NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, tmp, 500);
		if (bytesread <= 0)
			break ;
		tmp[bytesread] = '\0';
		tmp2 = ft_strdup(readfile);
		if (readfile)
			ft_memdel((void**)&readfile);
		readfile = ft_strjoin(tmp2, tmp);
		if (tmp2)
			ft_memdel((void**)&tmp2);
	}
	return (readfile);
}

int main(int ac, char **av)
{
	int		fd;
	char	*file;
	t_info	info;

	fd = 0;
	if (ac != 2)
		ft_printf("usage: ./fdf [filepath]\n");
	else
		fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error occured opening file.\n Make sure the file path is correct.\n");
		return (-1);
	}
	file = read_file(fd);
	info = get_info(file);
	draw(info);
	mlx_hook(info.win, 2, 0, key_pressed, &info);
	mlx_loop(info.mlx);
	return (0);
}

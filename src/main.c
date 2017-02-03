/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:44:12 by mvogee            #+#    #+#             */
/*   Updated: 2017/02/03 12:44:13 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** copys our original grid to be referenced later by the rot functions
** rotat the x y and z variables
** update the pts with the updated v3 matrix
** draw the new points to screen
*/

void	redraw_image(t_info info)
{
	t_v3	**tmp_v3grid;

	tmp_v3grid = copy_v3(info.v3grid, info);
	rotate_x(tmp_v3grid, info, info.xrot);
	rotate_y(tmp_v3grid, info, info.yrot);
	rotate_z(tmp_v3grid, info, info.zrot);
	info.pts = make_pts(info, tmp_v3grid);
	draw(info);
}

/*
** extention of key_pressed because couldnt fit it in 25 lines
*/

void	reset_rot(t_info *info, int keycode)
{
	if (keycode == 15)
	{
		info->xrot = 0;
		info->yrot = 0;
		info->zrot = 0;
	}
	else if (keycode == 126 || keycode == 125)
	{
		if (keycode == 126)
		{
			if (info->colors.index == 19)
				info->colors.index = 0;
			else
				info->colors.index += 1;
		}
		else if (keycode == 125)
		{
			if (info->colors.index == 0)
				info->colors.index = 19;
			else
				info->colors.index -= 1;
		}
		info->color = info->colors.colorarr[info->colors.index];
	}
}

/*
** makes the correct translation for the key pressed
*/

int		key_pressed(int keycode, t_info *info)
{
	float	angle;

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
	else if (keycode == 15 || keycode == 126 || keycode == 125)
		reset_rot(info, keycode);
	mlx_clear_window(info->mlx, info->win);
	redraw_image(*info);
	mlx_key_hook(info->win, key_pressed, info);
	return (0);
}

/*
** opens the file and reads all its contents into a char string
*/

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

/*
** initialize the info struct that will hold all the projection information.
** make sure there is input and that it is correct.
** open the file and read its contents into file char string
** get the info for the inital dawing of the image in get_info
** check for key hooks will make a change to the image
*/

int		main(int ac, char **av)
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
		ft_printf("Error occured opening file.\n");
		return (-1);
	}
	file = read_file(fd);
	info = get_info(file);
	draw(info);
	mlx_hook(info.win, 2, 0, key_pressed, &info);
	mlx_loop(info.mlx);
	return (0);
}

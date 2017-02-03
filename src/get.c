// 42 header goes here

#include "fdf.h"

int		get_numlines(char *file)
{
	int lines;

	lines = 0;
	while (file && *file)
	{
		if (*file == '\n')
			lines++;
		file++;
	}
	return (lines + 1);
}

int		get_numcols(char *file)
{
	int		cols;
	int		flag;

	cols = 0;
	flag = 0;
	while (file && *file && *file != '\n')
	{
		if (*file != ' ' && flag == 0)
		{
			flag = 1;
			cols++;
		}
		if (flag == 1 && *file == ' ')
			flag = 0;
		file++;
	}
	return (cols);
}

int		*get_zmap(char *file, int numlines, int numcols)
{
	int		*zmap;
	int		count;

	count = 0;
	zmap = (int*)malloc(sizeof(int) * numlines * numcols);
	while (file && *file)
	{
		if (ft_isdigit(*file))
		{
			zmap[count] = ft_atoi(file);
			count++;
			while (file && *file && ft_isdigit(*file))
				file++;
		}
		if (*file)
			file++;
	}	
	return (zmap);
}

/*
** sets all the variables in our lineinfo struct
*/

t_lineinfo	get_lineinfo(t_v2 v1, t_v2 v2)
{
	t_lineinfo lineinfo;

	lineinfo.x1 = v1.x;
	lineinfo.y1 = v1.y;
	lineinfo.x2 = v2.x;
	lineinfo.y2 = v2.y;
	lineinfo.x = lineinfo.x1;
	lineinfo.y = lineinfo.y1;
	lineinfo.dx = ft_abs(lineinfo.x2 - lineinfo.x1);
	lineinfo.dy = ft_abs(lineinfo.y2 - lineinfo.y1);
	if (lineinfo.x2 - lineinfo.x1 >= 0)
		lineinfo.sign_x = (lineinfo.x2 - lineinfo.x1 > 0 ? 1 : 0);
	else
		lineinfo.sign_x = -1;
	if (lineinfo.y2 - lineinfo.y1 >= 0)
		lineinfo.sign_y = (lineinfo.y2 - lineinfo.y1 > 0 ? 1 : 0);
	else
		lineinfo.sign_y = -1;
	lineinfo.swap = 0;
	return (lineinfo);
}

/*
** sets all the variables in our info struct
*/

t_info get_info(char *file)
{
	t_info	info;

	info.numlines = get_numlines(file);
	info.numcols = get_numcols(file);
	info.height = HEIGHT;
	info.width = WIDTH;
	info.zoom = HEIGHT / (info.numcols + info.numlines);
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "fdf");
	info.xrot = 0;
	info.yrot = 0;
	info.zrot = 0;
	info.zmap = get_zmap(file, info.numlines, info.numcols);
	info.v3grid = make_v3grid(info);
	info.pts = make_pts(info, info.v3grid);
	info.color = 0x000FFF3F;
	return (info);
}
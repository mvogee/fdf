// 42 header goes here

#include "fdf.h"
#include <stdio.h>

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

t_v3	**make_v3grid(t_info info) // goal of this is to go through the file and create
{
	int		count;
	int		count2;
	int		countz;
	t_v3	**grid;

	count = 0;
	countz = 0;
	grid = (t_v3**)malloc(sizeof(t_v3 *) * info.numlines + 1);
	while (count < info.numlines)
	{
		count2 = 0;
		grid[count] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		while (count2 < info.numcols)
		{
			grid[count][count2].x = info.zoom * (count2 - info.numcols / 2);
			grid[count][count2].y = info.zoom * (count - info.numlines / 2);
			grid[count][count2].z = (info.zoom / 2.5) * (info.zmap[countz]);
			printf("%.1f ",grid[count][count2].x);
			countz++;
			count2++;
		}
		printf("\n");
		count++;
	}
	return (grid);
}
//mesh[i][j] = vec3(mod*(j-columncount/2), mod*(i-rowcount/2), (mod/2.5)*ft_atoi(&line[linei]));
// this is saying mesh[i][j].x = vec3(mod*(j-columncount/2), vec3.y = mod*(i-rowcount/2), vec3.z = (mod/2.5)*ft_atoi(&line[linei]));


t_v2	**make_pts(t_info info)
{
	t_v2	**pts;
	int		x;
	int		y;

	x = 0;
	y = 0;
	pts = (t_v2**)malloc(sizeof(t_v2*) * info.numlines);
	while (y < info.numlines)
	{
		pts[y] = (t_v2*)malloc(sizeof(t_v2) * info.numcols);
		y++;
	}
	y = 0;
	while (y < info.numlines - 1)
	{
		while (x < info.numcols)
		{
			pts[y][x].x = info.v3grid[y][x].x + info.width / 2;
			pts[y][x].y = info.v3grid[y][x].y + info.height / 2;
			x++;
		}
		x = 0;
		y++;
	}
	return	(pts);
}

//	points[row][col] = vec2(X + v.size/2 + v.proportionality*X*Z, Y + v.size/2 + v.proportionality*Y*Z); // the X Y Z vars are v3d_grid[y][x].x y or z
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
			while (file && ft_isdigit(*file))
				file++;
		}
		if (*file)
			file++;
	}	
	return (zmap);
}

int		ft_abs(int i)
{
	return i < 0 ? -i : i;
}

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
#include <stdio.h>
t_info get_info(char *file)
{
	t_info	info;

	info.numlines = get_numlines(file);
	info.numcols = get_numcols(file);
	info.height = HEIGHT;
	info.width = WIDTH;
	info.zoom = WIDTH / info.numcols; // this is our mod
//	info.prop = 0.0012; // this deals with warping the plane if you want to. not nessesary
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "fdf");
	info.xrot = 0;
	info.yrot = 0;
	info.zrot = 0;
	info.zmap = get_zmap(file, info.numlines, info.numcols);
	info.v3grid = make_v3grid(info);
	info.pts = make_pts(info);
	return (info);
}
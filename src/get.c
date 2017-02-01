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
	return (lines);
}

int		get_numcols(char *file)
{
	int		cols;
	int		flag;

	cols = 0;
	flag = 0;
	while (file && *file)
	{
		if (*file != ' ' && flag == 0 && *file != '\n')
		{
			flag = 1;
			cols++;
		}
		if (flag == 1 && (*file == ' ' || *file == '\n'))
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
	t_v3 **grid;

	count = 0;
	countz = 0;
	grid = (t_v3**)malloc(sizeof(t_v3 *) * info.numlines + 1);
	while (count < info.numlines)
	{
		count2 = 0;
		grid[count] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		while (count2 < info.numcols)
		{
			grid[count][count2].x = info.zoom * (count2 - info.numcols);
			grid[count][count2].y = info.zoom * (count - info.numlines);
			grid[count][count2].z = (info.zoom / 2.5) * (info.zmap[countz]);
			countz++;
			count2++;
		}
		count++;
	}
	return (grid);
}
//mesh[i][j] = vec3(mod*(j-columncount/2), mod*(i-rowcount/2), (mod/2.5)*ft_atoi(&line[linei]));
// this is saying mesh[i][j].x = vec3(mod*(j-columncount/2), vec3.y = mod*(i-rowcount/2), vec3.z = (mod/2.5)*ft_atoi(&line[linei]));


t_v2	**make_pts(t_info info) // go through the 
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
		while (x < info.numcols)
		{
			pts[y][x].x = info.v3grid[y][x].x + info.width / 2;
			pts[y][x].y = info.v3grid[y][x].y + info.height / 2;
			x++;
		}
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

t_lineinfo	get_lineinfo(t_v2 v1, t_v2 v2, t_info info)
{
	t_lineinfo lineinfo;

	lineinfo.x1 = v1.x;
	lineinfo.y1 = v1.y;
	lineinfo.x2 = v2.x;
	lineinfo.y2 = v2.y;
	lineinfo.x = x1;
	lineinfo.y = y1;
	lineinfo.dx = abs(x2 - x1);
	lineinfo.dy = abs(y2 - y1);
	if (x2 - x1 >= 0)
		lineinfo.sign_x = (x2 - x1 > 0 ? 1 : 0);
	else
		lineinfo.sign_x = -1;
	if (y2 - y1 >= 0)
		lineinfo.sign_y = (y2 - y1 > 0 ? 1 : 0);
	else
		lineinfo.sign_y = -1;
	lineinfo.dir = 0;
	lineinfo.temp = 0;
	return (lineinfo);
}

t_info get_info(int numcols, int numlines, char *file)
{
	t_info	info;

	info.numlines = numlines;
	info.numcols = numcols;
	info.height = HEIGHT;
	info.width = WIDTH;
	info.zoom = numcols / 2; // this is our mod
//	info.prop = 0.0012; // this deals with warping the plane if you want to. not nessesary
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "fdf");
	info.xrot = 0;
	info.yrot = 0;
	info.zrot = 0;
//	info.midx = 
	info.zmap = get_zmap(file, info.numlines, info.numcols);
	info.v3grid = make_v3grid(info);
	info.pts = make_pts(info); // make this
	return (info);
}
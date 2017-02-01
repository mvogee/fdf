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

	cols = -1;
	flag = 0;
	while (file && *file)
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

t_v3	**get_v3grid(t_info info, char *file) // goal of this is to go through the file and create
{
	int count;
	int count2;
	t_v3 **grid;

	count = 0;
	grid = (t_v3**)malloc(sizeof(t_v3 *) * info.numlines + 1);
	while (count < info.numlines)
	{
		count2 = 0;
		grid[count] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		while (count2 < info.numcols)
		{
			grid[count][count2] = grid()
		}

	}
}

t_v2	**get_pts(t_info info) // go through the 
{
	t_v2	**pts;
	int		x;
	int		y;

	x = 0;
	y = 0;

	pts = (t_v2**)malloc(sizeof(t_v2*) * info.numlines + 1);
	while (y < info.numlines)
	{
		pts[y][x] = (t_v2*)malloc(sizeof(t_v2) * info.numcols + 1);
	}
}
	points[row][col] = vec2(X + v.size/2 + v.proportionality*X*Z, Y + v.size/2 + v.proportionality*Y*Z);
mesh[i][j] = vec3(mod*(j-columncount/2), mod*(i-rowcount/2), (mod/2.5)*ft_atoi(&line[linei]));
// this is saying mesh[i][j] vec3.x = vec3(mod*(j-columncount/2), vec3.y = mod*(i-rowcount/2), vec3.z = (mod/2.5)*ft_atoi(&line[linei]));

t_info get_info(int numcols, int numlines, char *file)
{
	t_info	info;

	info.numlines = numlines;
	info.numcols = numcols;
	info.height = HEIGHT;
	info.width = WIDTH;
	info.zoom = 50;
	info.prop = 0.0012; // why this number?
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "fdf");
	info.xrot = 0;
	info.yrot = 0;
	info.zrot = 0;
	info.midx = 
	info.v3grid = get_v3grid(numcols, numlines, file); // make this
	info.pts = get_pts(numcols, numlines, file); // make this
	return (info);
}
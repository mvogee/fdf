// 42 header here

#include "fdf.h"

void	draw(t_info info)
{
	int y;
	int x;
	t_v2 **points;

	points = info.pts;
	y = 0
	while (y < info.numlines - 2)
	{
		x = 0
		while (x < info.numcols - 1)
		{
			draw_bres_line(points[y][x], points[y][x + 1], info);
			draw_bres_line(points[y][x], points[y + 1][x], info);
			x++;
		}
		draw_bres_line(points[y][x], points[y + 1][x], info);
		y++;
	}
	x = 0;
	while (x < info.numcols - 1; x++)
	{
		draw_bres_line(points[y][x], points[y][ x+ 1], info);
		x++;
	}
}

get_linedir(double dy, double dx)
{
	double dir;
		if (dy > dx) 
	{ 
		temp = dx;
		dx = dy;
		dy = temp;
		dir = 1;
	}
	return (dir);
}

//implements Bresenham's line algorithm
void	draw_bres_line(t_v2 v1, t_v2 v2, t_info info)
{
	t_lineinfo	lineinfo;
	int count;
	float derr;

	lineinfo = get_lineinfo(v1, v2, info);
	lineinfo.dir = get_linedir(lineinfo.dy, lineinfo.dx);
	derr = 2 * lineinfo.dy - lineinfo.dx;
	count = 0;
	while (count < lineinfo.dx)
	{
		mlx_pixel_put(info.mlx, info.win, lineinfo.x, lineinfo.y, 0x00550000);
		while (derr >= 0)
		{ 
			derr = derr - 2 * lineinfo.dx; 
			if (lineinfo.dir)
				lineinfo.x += lineinfo.sign_x; 
			else 
				lineinfo.y += lineinfo.sign_y; 
		}
		derr = derr + 2 * lineinfo.dy;
		if (lineinfo.dir)
			lineinfo.y += lineinfo.sign_y;
		else 
			lineinfo.x += lineinfo.sign_x;
		count++;
	}
}
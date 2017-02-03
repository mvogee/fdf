// 42 header here

#include "fdf.h"
#include <stdio.h>

double get_linedir(t_lineinfo *lineinfo)
{
	double swap;
	double temp;

	swap = 0;
	temp = 0;
	if (lineinfo->dy > lineinfo->dx) 
	{
		temp = lineinfo->dx;
		lineinfo->dx = lineinfo->dy;
		lineinfo->dy = temp;
		swap = 1;
	}
	return (swap);
}

void	draw_bres_line(t_v2 v1, t_v2 v2, t_info info)
{
	t_lineinfo	lineinfo;
	int count;

	lineinfo = get_lineinfo(v1, v2);
	lineinfo.swap = get_linedir(&lineinfo);
	lineinfo.derr = 2 * lineinfo.dy - lineinfo.dx;
	count = 0;
	while (count < lineinfo.dx)
	{
		mlx_pixel_put(info.mlx, info.win, lineinfo.x, lineinfo.y, 0x00FFFFFF);
		while (lineinfo.derr >= 0)
		{ 
			lineinfo.derr = lineinfo.derr - 2 * lineinfo.dx; 
			if (lineinfo.swap != 0)
				lineinfo.x += lineinfo.sign_x;
			else
				lineinfo.y += lineinfo.sign_y;
		}
		lineinfo.derr = lineinfo.derr + 2 * lineinfo.dy;
		if (lineinfo.swap)
			lineinfo.y += lineinfo.sign_y;
		else 
			lineinfo.x += lineinfo.sign_x;
		count++;
	}
}

void	draw(t_info info)
{
	int y;
	int x;
	t_v2 **points;

	points = info.pts;
	y = 0;
	while (y < info.numlines - 2)
	{
		x = 0;
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
	while (x < info.numcols - 1)
	{
		draw_bres_line(points[y][x], points[y][x + 1], info);
		x++;
	}
}
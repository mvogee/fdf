// 42 header here

#include "fdf.h"

/*
** all using "Simple", vector math to tanslate the vector map points
*/

void	rotate_x(t_v3 **v3grid, t_info info, float angle)
{
	float	yp;
	float	zp;
	int		y;
	int		x;

	y = 0;
	while (y < info.numlines - 1)
	{
		x = 0;
		while (x < info.numcols)
		{
			yp = v3grid[y][x].y * cos(angle) - v3grid[y][x].z * sin(angle);
			zp = v3grid[y][x].z * cos(angle) + v3grid[y][x].y * sin(angle);
			v3grid[y][x].y = yp;
			v3grid[y][x].z = zp;
			x++;
		}
		y++;
	}
}

void	rotate_y(t_v3 **v3grid, t_info info, float angle)
{
	float	xp;
	float	zp;
	int		y;
	int		x;

	y = 0;
	while (y < info.numlines - 1)
	{
		x = 0;
		while (x < info.numcols)
		{
			xp = v3grid[y][x].x * cos(angle) - v3grid[y][x].z * sin(angle);
			zp = v3grid[y][x].z * cos(angle) + v3grid[y][x].x * sin(angle);
			v3grid[y][x].z = zp;
			v3grid[y][x].x = xp;
			x++;
		}
		y++;
	}
}

void	rotate_z(t_v3 **v3grid, t_info info, float angle)
{
	float	xp;
	float	yp;
	int		y;
	int		x;

	y = 0;
	while (y < info.numlines - 1)
	{
		x = 0;
		while (x < info.numcols)
		{
			xp = v3grid[y][x].x * cos(angle) - v3grid[y][x].y * sin(angle);
			yp = v3grid[y][x].x * sin(angle) + v3grid[y][x].y * cos(angle);
			v3grid[y][x].x = xp;
			v3grid[y][x].y = yp;
			x++;
		}
		y++;
	}
}


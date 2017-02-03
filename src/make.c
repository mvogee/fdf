/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:45:20 by mvogee            #+#    #+#             */
/*   Updated: 2017/02/03 12:45:24 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_abs(int i)
{
	return (i < 0 ? -i : i);
}

t_v3		**copy_v3(t_v3 **v3grid, t_info info)
{
	int			y;
	int			x;
	t_v3		**tmp_v3grid;

	y = 0;
	tmp_v3grid = (t_v3 **)malloc(sizeof(t_v3*) * info.numlines + 1);
	while (y < info.numlines)
	{
		tmp_v3grid[y] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		y++;
	}
	y = 0;
	while (y < info.numlines - 1)
	{
		x = 0;
		while (x < info.numcols)
		{
			tmp_v3grid[y][x] = v3grid[y][x];
			x++;
		}
		y++;
	}
	return (tmp_v3grid);
}

/*
** creates a ed array of vector3s corresponding to all the vectors on the map
*/

t_v3		**make_v3grid(t_info info)
{
	int			count;
	int			count2;
	int			countz;
	t_v3		**grid;

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
			grid[count][count2].z = (info.zoom / 2) * (info.zmap[countz]);
			countz++;
			count2++;
		}
		count++;
	}
	return (grid);
}

t_v2		**make_pts(t_info info, t_v3 **v3grid)
{
	t_v2		**pts;
	int			x;
	int			y;

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
			pts[y][x].x = v3grid[y][x].x + info.width / 2;
			pts[y][x].y = v3grid[y][x].y + info.height / 2;
			x++;
		}
		x = 0;
		y++;
	}
	return (pts);
}

t_colors	make_colorstruct(void)
{
	t_colors	colorstruct;

	colorstruct.index = 0;
	colorstruct.colorarr[0] = 0x00FFFFFF;
	colorstruct.colorarr[1] = 0x0000FFFF;
	colorstruct.colorarr[2] = 0x00FFFF00;
	colorstruct.colorarr[3] = 0x00FFF00F;
	colorstruct.colorarr[4] = 0x00FF0000;
	colorstruct.colorarr[5] = 0x00F0FFFF;
	colorstruct.colorarr[6] = 0x080600FF;
	colorstruct.colorarr[7] = 0x00000FFF;
	colorstruct.colorarr[8] = 0x000000FF;
	colorstruct.colorarr[9] = 0x00FFF0FF;
	colorstruct.colorarr[10] = 0x00FF00FF;
	colorstruct.colorarr[11] = 0x00F0F00F;
	colorstruct.colorarr[12] = 0x00F0FF00;
	colorstruct.colorarr[13] = 0x0000FF00;
	colorstruct.colorarr[14] = 0x00FF108F;
	colorstruct.colorarr[15] = 0x00F88F00;
	colorstruct.colorarr[16] = 0x00800080;
	colorstruct.colorarr[17] = 0x0F0000FF;
	colorstruct.colorarr[18] = 0x0F808080;
	colorstruct.colorarr[19] = 0x00080800;
	return (colorstruct);
}

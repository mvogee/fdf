#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define HEIGHT 750
# define WIDTH 950


typedef struct	s_v2
{
	float	x;
	float	y;
}				t_v2;

typedef struct	s_v3
{
	float	x;
	float	y;
	float	z;
}				t_v3;

typedef struct	s_lineinfo
{
	float x1;
	float x2;
	float y1;
	float y2;
	double x;
	double y;
	double dx;
	double dy;
	double sign_x;
	double sign_y;
	double dir;
	double temp;
}				t_lineinfo;

typedef struct	s_info
{
	void	*mlx;
	void	*win;
	int		numlines;
	int		numcols;
	int		height;
	int		width;
	int		zoom;
	float	prop;
	int		*zmap;
	t_v3	**v3grid;
	t_v2	**pts;
	float	xrot;
	float	yrot;
	float	zrot;
	int		midx;
	int		midy;
}				t_info;

/*
** mian.c
*/
int		main(int ac, char **av);
char	*read_file(int fd);
/*
** get.c
*/
int		get_numlines(char *file);
int		get_numcols(char *file);
int		*get_zmap(char *file, int numlines, int numcols);
t_info	get_info(int numcols, int numlines, char *file);
/*
** make.c
*/
t_v3	**make_v3grid(t_info info);
t_v2	**make_pts(t_info info);
/*
** draw.c
*/
void	draw_bres_line(t_vec2 vec1, t_vec2 vec2, t_view v);
void	draw(t_info info);


#endif

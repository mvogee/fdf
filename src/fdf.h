#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define HEIGHT = 800
# define WIDTH = 1000


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


#endif

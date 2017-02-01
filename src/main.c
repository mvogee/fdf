//42 header goes here

#include "fdf.h"

char	*read_file(int fd)
{
	char	*readfile;
	char	tmp[500];
	char	*tmp2;
	int		bytesread;

	bytesread = read(fd, tmp, 500);
	tmp[bytesread] = '\0';
	readfile = ft_strdup(tmp);
	if (!readfile)
		return (NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, tmp, 500);
		if (bytesread <= 0)
			break ;
		tmp[bytesread] = '\0';
		tmp2 = ft_strdup(readfile);
		if (readfile)
			ft_memdel((void**)&readfile);
		readfile = ft_strjoin(tmp2, tmp);
		if (tmp2)
			ft_memdel((void**)&tmp2);
	}
	return (readfile);
}


int main(int ac, char **av)
{
	int		fd;
	char	*file;
	int		numcols;
	int		numlines;

	fd = 0;
	if (ac != 2)
		ft_printf("usage: ./fdf [filepath]\n");
	else
		fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error occured opening file.\n Make sure the file path is correct.\n");
		return (-1);
	}
	file = read_file(fd);
	numcols = get_numcols(file);
	numlines = get_numlines(file);
	get_info(numcols, numlines, file);
	draw(info); // this needs to be made
	mlx_hook(info.win, 2, 0, keyboard_event, &info);
	mlx_loop(info.mlx);
	return (0);
}

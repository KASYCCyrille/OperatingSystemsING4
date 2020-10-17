#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *path)
{
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(0);
}

int main(void)
{
	char	*path1, *path2, c;
	int		fd_txt1, fd_txt2, byte_read;
	
	path1 = "./text1.txt";
	path2 = "./text2.txt";
	if ((fd_txt1 = open(path1, O_RDONLY)) == -1)
		ft_error(path1);
	if ((fd_txt2 = open(path2, O_WRONLY)) == -1)
		ft_error(path2);
	dup2(fd_txt2, 1);
	while ((byte_read = read(fd_txt1, &c, 1)) > 0)
		write(1, &c, byte_read);
	if (byte_read == -1)
		ft_error(path1);
	close(fd_txt1);
	close(fd_txt2);
	return (0);
}

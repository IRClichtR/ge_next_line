#include "get_next_line_bonus.h"

char	*join_nfree(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*get_charleft(int fd, char *charleft)
{
	char	*buff;
	int		r_bytes;

	if (!charleft)
		charleft = ft_calloc(1, 1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff || !charleft)
		return (NULL);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(fd, buff, BUFFER_SIZE);
		if (r_bytes == 0)
			return (charleft);
		if (r_bytes < 0)
			return (free(buff), NULL);
		buff[r_bytes] = '\0';
		charleft = join_nfree(charleft, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	free(buff);
	return (charleft);
}

char	*get_line(char *charleft, char *line)
{
	int		i;
	int		len;
	
	len = 0;
	if (!charleft)
		return (NULL);
	while (charleft[len] && charleft[len] != '\n')
		len++;
	line = malloc(sizeof(char) * len + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (charleft[i] && charleft[i] != '\n')
	{
		line[i] = charleft[i];
		i++;
	}
	if (charleft[i] == '\n')
		line[i++] = '\n';
	else
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

char	*get_new_charleft(char *charleft)
{
	char	*new_charleft;
	int		i;
	int		j;

	i = 0;
	while (charleft[i] && charleft[i] != '\n')
		i++;
	if (!charleft[i])
	{
		free(charleft);
		return (NULL);
	}
	new_charleft = malloc(sizeof(char) * (ft_strlen(charleft) - i + 1));
	i++;
	j = 0;
	while (charleft[i])
		new_charleft[j++] = charleft[i++];
	new_charleft[j] = '\0';
	free(charleft);
	return (new_charleft);
}

char	*get_next_line(int fd)
{
	static char	*charleft[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	charleft[fd] = get_charleft(fd, *charleft);
	if (!charleft[fd])
		return (NULL);
	line = get_line(charleft[fd], line);
	charleft[fd] = get_new_charleft(charleft[fd]);
	if (line == NULL)
		free(charleft[fd]);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("lorem_ipsum", O_RDONLY);
	char	*line;

	line  = get_next_line(fd);
	printf("line read = %s\n", line);
	printf("______________________________________________________________\n\n");
	while (fd != -1 && line != NULL)
	{
		line  = get_next_line(fd);
		printf("line read = %s\n", line);
		printf("______________________________________________________________\n\n");
		free(line);
	}
	close(fd);
	return (0);
}	

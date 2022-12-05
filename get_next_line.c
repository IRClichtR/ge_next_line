#include "get_next_line.h"
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*copy;
	char	*str;

	i = 0;
	str = (char *)s;
	copy = malloc(sizeof (char) * ft_strlen(str) + 1);
	if (copy == NULL)
	{
		free(copy);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*join_nfree(char *s1, char *s2)
{
	char	*tmp;
	
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
	if (!charleft)
		return (NULL);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(fd, buff, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free (buff);
			return (NULL);
		}
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
	while (charleft[len] != '\0')
		len++;
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len && charleft[len] != '\n')
	{
		line[i] = charleft[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_new_charleft(char *charleft, char *line)
{
	char	*new_charleft;
	int		i;

	i = 0;
	while (charleft[i] == line[i])
		i++;
	if (charleft[i] == '\0')
		return (NULL);
	new_charleft = ft_strdup(&charleft[i]);
	free(charleft);
	return (new_charleft);
}

char	*get_next_line(int fd)
{
	static char	*charleft;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	charleft = get_charleft(fd, charleft);
	printf("charleft : %s\n", charleft);
	if (!charleft)
		return (NULL);
	line = get_line(charleft, line);
	printf("coucou\n");
	charleft = get_new_charleft(charleft, line);
	return (line);
}

#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("lorem_ipsum.txt", O_RDONLY);
	char	*line;

	while (fd != -1)
	{
		line  = get_next_line(fd);
		printf("line read = %s\n", line);
		free(line);
	}	
}

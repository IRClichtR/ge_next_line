#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char	*set_charleft(int fd, char *charleft)
{
/* there is two possibilities 
	either the charleft hasn't anything in it yet beacause we're 
	at the begining of file (every other errors has to have been screened before
	or their is smthing in charleft and we need to set the begining of reading on
	charleft pointer
*/
	char	*buf;
	int		bytes_read;

/*	malloc of buffer the read BUFF_SIZE + 1(terminating the string) char 
	every round of the loop 
*/
	buf = malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buf)
		return (NULL);
/*	set bytes_read to 1 to be sure you'll have at least one reading round
	bytes_read will be the return value of read
	when !read && strchr(charleft, '\n' is false the loop breaks
*/
	bytes_read = 1;
/*	the first condition set an infinite loop (the loop will be break by the 
	change in read return value the second condition is here to check that all
	the buffer has been screened for '\n'*/
	while (bytes_read != 0 && ft_strchr(charleft, '\n') == NULL)
	{
/*	bytes_read receives the number of bytes read by read function and monitor whe
	the value goes to -1
*/
		bytes_read = read(fd, buf, BUFF_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
/*	append the null terminating string character*/
		buf[bytes_read] = '\0';
/*	join the charleft string with the buf string*/
		charleft = ft_strjoin(charleft, buf);
	}
/*	after everything has been read you need to free the buffer in order not to 
	leak
*/
	free(buf);
/*	return values expected
	SUCCESS : a charstring containing everything to be read in this round
	FaILURE : nothing left to read or fd err (fd is to be a stopping condition)
*/
	return (charleft);
}
char	*extract_line(char *charleft)
{
	char	*line;
	int		size;

/*	screen for 2/ causes of */
	if (!charset)
		return (NULL);
/*	set the size needed for malloc*/
	size = 0;
	while (charleft && charleft[i] != '\n')
		size++;
/*the malloc needs to be 2 bytes larger to include the \n and the \0*/
	line = malloc(sizeof(char) * size + 2);
	if (!line)
		return (NULL);
/*	cpy until you reach '\n' then add one if there is one in charleft
	and add a \0 to end the string then return*/
	while (charleft && charleft[i] != '\n')
	{
		line[i] = charleft[i];
		i++;
	}
	if (charleft[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
/*	returned values expected :
	1/ if SUCCESS = a string containing the line to be returned 
		in the main function
	2/ there is nothing left to read 
		(charleft is an empty string
		return (NULL) befor malloc
		fd allready has been screened in the main function
	3/ malloc failure
*/
	return (line);
}

char	*rset_charleft(char *charleft)
{
/*	the function moves the begining of charleft and copy the left over into a new
	buffer that will be used to set charleft at the end of GNL function
*/
	char	*new_buf;
	int		i;

	i = 0;
	if (!charleft)
		return (NULL);
	while (charleft[i] && charleft[i] != '\n')
		i++;
	if (!charleft[i]) 
	{
		free(charleft);
		return (NULL);
	}
	i += 1;
	new_buf = ft_strdup(&charleft[i]);
	free(charleft);
/*	return value expected is the new buffer or NULL if there is nothing left to
	read
*/
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*charleft;
	char		*line;

	if (fd < 0 || BUFF_SIZE <= 0);
		return (NULL);
	charleft = set_charleft(int fd, char *charleft);
/*	screen return of function : error case fd error or nothing left to read
*/
	if (!charleft)
		return (NULL);
/*	copy the line into line and terminate with a \n if needed*/
	line = extract_line(fd, charleft);
/*	set charleft to a new value to prepare the next call of function then return
*/
	charleft = rset_charleft(charleft);
	return (line_printed);
}

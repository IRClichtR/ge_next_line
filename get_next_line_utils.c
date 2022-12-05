#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (SIZE_MAX) / size)
		return (NULL);
	array = malloc(size * nmemb);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, nmemb * size);
	return (array);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str1;
	char			*str2;
	char			*cat_str;
	unsigned int	i;
	unsigned int	j;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	j = 0;
	cat_str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!cat_str)
		return (NULL);
	while (str1[i] != '\0')
	{
		cat_str[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		cat_str[i + j] = str2[j];
		j++;
	}
	cat_str[i + j] = '\0';
	return (cat_str);
}

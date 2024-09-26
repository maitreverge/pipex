#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	buffer = malloc(size * count);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * count);
	return (buffer);
}


char *generate_random_string(size_t length)
{
	long unsigned int	seed;
	size_t				len_ascii;
	size_t				i;
	char				*result;
	char				*ascii;

	i = -1;
	ascii = "123456789qwertyuiopasdfghjklzxcvbnm";
	len_ascii = strlen(ascii);
	result = (char*)ft_calloc(sizeof(char), length);
	if (!result)
		return NULL;
	seed = (long unsigned int)&length;
	while (++i < length)
	{
		result[i] = ascii[(i + seed) % len_ascii];
	}
	return result;
}

int main() {
    char *random_string = generate_random_string(2);
    printf("Random String: %s\n", random_string);
    free(random_string);
    return 0;
}
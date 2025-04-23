#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char	*buf;
	size_t	size;

	size = 64;
	buf = malloc(size * sizeof(*buf));
	if (!buf)
		return (1);
	while (!getcwd(buf, size))
	{
		free(buf);
		size += 64;
		buf = malloc(size * sizeof(*buf));
		if (!buf)
			return (1);
	}
	printf("%s", buf);
	free(buf);
	return (0);
}

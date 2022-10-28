#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	struct timeval time_set;

	gettimeofday(&time_set, NULL);
	printf("%ld:%ld\n", time_set.tv_sec, time_set.tv_usec);
	return (0);
}

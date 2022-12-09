#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

/*long long get_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000)); //밀리 세컨은 1000분의 1초.
}*/


int	main(void)
{
	struct timeval now, fin;
	long diff_sec;
	long diff_usec;
	long diff_time;
	long mstime;

	gettimeofday(&now, NULL);
	usleep(1000000);
	gettimeofday(&fin, NULL);
	diff_sec = fin.tv_sec - now.tv_sec;
	diff_usec = fin.tv_usec - now.tv_usec;
	diff_time = diff_sec + ((double)diff_usec / 1000000);
	mstime = (fin.tv_sec - now.tv_sec) * 1000 + (fin.tv_usec - now.tv_usec) / 1000;
	printf("diff ms time is %ld ms. \n", mstime);
	printf("diff time: %ld s\n", diff_time);
}
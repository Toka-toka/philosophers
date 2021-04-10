#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_all
{
	pthread_t		wizard;
	pthread_t		philo;
	pthread_mutex_t	display;
}				t_all;

void    *life(void *all)
{
	t_all	*data;

	data = (t_all *)all;  
    pthread_detach(data->philo);
    sleep(5);
    return(NULL);
}

int main()
{
	t_all all;
    
    pthread_create(&all.philo, NULL, life, (void *)&all);
    pthread_join(all.philo, NULL);
    pthread_detach(all.philo);
    sleep(1);
    exit(0);
}
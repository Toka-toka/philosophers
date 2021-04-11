#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int     value;

typedef struct	s_philo
{
	pthread_t		ptr;
	pthread_mutex_t	*out;
    int             stop;
}				t_philo;

typedef struct	s_all
{
	t_philo		*wizard;
	t_philo		*philo;
	pthread_mutex_t	display;

}				t_all;

void    *life(void *data)
{
	t_all	*all;

	all = (t_all *)data;
//    while (1)
//    {
        scanf("%d", &value);
//        usleep(1000 * 1000);
//        pthread_mutex_lock(all->philo->out);
//        if (value == 10) 
//            printf("Hello, im philo\n");
//        if (all->philo->stop == 1) 
//            return(NULL);
//        pthread_mutex_unlock(all->philo->out);
//    }
    return(NULL);
}

void    *work(void *data)
{
	t_all	*all;
    int time;

	all = (t_all *)data;
    pthread_mutex_lock(all->wizard->out);
    time = 3000;
    while (1)
    {
        if (value == 10)
        {
            printf("You are right!\n");
            return(NULL);
        }
        if (time < 0)
        {
            pthread_cancel(all->philo->ptr);
            printf("You time is over!\n");
            return(NULL);
        }
        time -= 100;
        usleep(100 * 1000);
    }
    printf("Hello, im wizard\n");
    all->philo->stop = 1;
    pthread_mutex_unlock(all->wizard->out);
    return(NULL);
}

int main()
{
	t_all all;
    t_philo philo;
    t_philo wizard;

    all.philo = &philo;
    all.wizard = &wizard;
    
    value = 0;
    pthread_mutex_init(&all.display, NULL);
    philo.out = &all.display;
    wizard.out = &all.display;
    all.philo->stop = 0;
    pthread_create(&philo.ptr, NULL, life, (void *)&all);
    pthread_create(&wizard.ptr, NULL, work, (void *)&all);
    pthread_join(wizard.ptr, NULL);
    pthread_join(philo.ptr, NULL);
    exit(0);
}
#include "philo.h"

void    waid(useconds_t time)
{
    useconds_t end = 0;
    struct timeval get_time;
    while ((time - end) > 0)
    {
        usleep(10);
        gettimeofday(&get_time, NULL);
        end = get_time.tv_sec * 1000 + get_time.tv_usec / 1000;
    }
}

void    *work(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    pthread_mutex_lock(philo->mutex);
    printf("Hello, im philo №%d\n", philo->number);
    pthread_mutex_unlock(philo->mutex);
    return(NULL);
}

void    create_phylo(t_all *all)
{
    int i;

    i = 0;
    all->philo_ptr = malloc(all->philo_num * sizeof(t_philo));
    while (i < all->philo_num)
    {
        all->philo_ptr[i].number = i;
        all->philo_ptr[i].mutex = &all->mutex;
        pthread_create(&all->philo_ptr[i].ptr, NULL, work, (void *)&all->philo_ptr[i]);
        usleep(1000);
        i++;
    }
}

int main()
{
    t_all all;
    int i;
//    struct timeval start, end;    

    i = 0;
    all.philo_num = 10;
    pthread_mutex_init(&all.mutex, NULL);
    create_phylo(&all);
	while (i < all.philo_num)
	{
		pthread_join(all.philo_ptr[i].ptr, NULL);
        i++;
	}
//    gettimeofday(&start, NULL);
//    usleep(10000);
//    waid(1000*1000); // микро
//    gettimeofday(&end, NULL);
//    printf("%ld mill seconds\n",
//    (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000));
    return(0);
}
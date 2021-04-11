#include "philo.h"

void	life1(void * data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->out);
	printf("%10.ld Hello, im philo №%d\n", get_time(philo->hungry), philo->number + 1);
	usleep(1000 * 1000);
	pthread_mutex_unlock(philo->out);
}

void	*life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_detach(philo->ptr);
	while (1)
	{
		life1(data);
		usleep(500 * 1000);
	}
	return (NULL);
}

void	*death_catch(void *data)
{
	t_all	*all;
	int i;

	i = 0;
	all = (t_all *)data;
//	printf("number = %d\n", all.number);
	usleep(10000 * 1000);
	while (i < all->lim->philo)
	{
//		pthread_detach(all->philo_ptr[i].ptr);
		i++;
	}
//	printf("Hello, im wizard\n");
//	pthread_mutex_destroy(philo->out);
	return(NULL);
}

int	start_party(t_all *all)
{
	int	i;
	
	i = 0;
//	gettimeofday(&all->start, NULL);
	while (i < all->lim->philo)
	{
		if (i % 2 == 0)
		{
//			all->philo_ptr[i].hungry = all->start;
			gettimeofday(&all->philo_ptr[i].hungry, NULL);
			pthread_create(&all->philo_ptr[i].ptr, NULL, life,
				(void *)&all->philo_ptr[i]);
		}
		i++;
	}
	i = 0;
	usleep(60);
	while (i < all->lim->philo)
	{
		if (i % 2 != 0)
		{
//			all->philo_ptr[i].hungry = all->start;
			gettimeofday(&all->philo_ptr[i].hungry, NULL);
			pthread_create(&all->philo_ptr[i].ptr, NULL, life,
				(void *)&all->philo_ptr[i]);
		}
		i++;
	}
	pthread_create(&all->wizard, NULL, death_catch,(void *)&all);
	pthread_join(all->wizard, NULL);
	i = 0;
/*	while (i < all->lim->philo)
	{
		pthread_join(all->philo_ptr[i].ptr, NULL);
		i++;
	}*/
	free(all->philo_ptr);
	return (0);
}
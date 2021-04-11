#include "philo.h"

void    block_print(t_philo *philo, char *str)
{
    pthread_mutex_lock(philo->out);
    if (philo->stop == 0)
        printf("%10.ld %d %s\n", get_time(philo->lim->start), philo->index + 1, str);
    pthread_mutex_unlock(philo->out);
}

void	fork_left(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
//    block_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->right);
//    block_print(philo, "has taken a fork");
}

void	fork_take(t_philo *philo)
{
	if (philo->index % 2 == 0)
    {
        pthread_mutex_lock(philo->left);
        block_print(philo, "has taken a fork");
	    pthread_mutex_lock(philo->right);
        block_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right);
        block_print(philo, "has taken a fork");
	    pthread_mutex_lock(philo->left);
        block_print(philo, "has taken a fork");
    }
}

void	*life(void *data)
{
	t_philo	*philo;

    int check;

	philo = (t_philo *)data;
    while (philo->stop == 0)
    {
//	    pthread_detach(philo->ptr);
		fork_take(philo);
        gettimeofday(&philo->hungry, NULL);
        block_print(philo, "is eating");
        usleep(philo->lim->eat * 1000);
        fork_left(philo);
        block_print(philo, "is sleeping");
        usleep(philo->lim->sleep * 1000);
        block_print(philo, "is thinking");
	}
	return (NULL);
}

void	*death_catch(void *data)
{
	t_all	*all;

	int i;

	i = 0;
	all = (t_all *)data;
    gettimeofday(&all->lim->start, NULL);
    while(1)
    {
	    i = 0;
        while (i < all->lim->philo)
	    {
            if (get_time(all->philo[i].hungry) > all->lim->die)
            {
                printf("%d Die!", all->philo[i].index + 1);
                exit(0);
            }
            i++;
        }
    }
	return(NULL);
}

int	start_party(t_all *all)
{
	int	i;
	
	i = 0;
    gettimeofday(&all->lim->start, NULL);
	while (i < all->lim->philo)
	{
//		if (i % 2 == 0)
//		{
            gettimeofday(&all->philo[i].hungry, NULL);
			pthread_create(&all->philo[i].ptr, NULL, life,
				(void *)&all->philo[i]);
//		}
		i++;
        usleep(10);
	}
	i = 0;
/*	while (i < all->lim->philo)
	{
		if (i % 2 != 0)
		{
			gettimeofday(&all->philo[i].hungry, NULL);
			pthread_create(&all->philo[i].ptr, NULL, life,
				(void *)&all->philo[i]);
		}
		i++;
	}*/
	pthread_create(&all->wizard, NULL, death_catch,(void *)all);
	pthread_join(all->wizard, NULL);
	i = 0;
/*	while (i < all->lim->philo)
	{
		pthread_join(all->philo[i].ptr, NULL);
		i++;
	}*/
	free(all->philo);
	return (0);
}
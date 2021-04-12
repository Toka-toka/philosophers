#include "philo.h"

int	block_print(t_philo *philo, char *str, char *color)
{	
	static char	end;

	pthread_mutex_lock(philo->out);
	if (end == 1)
	{
		pthread_mutex_unlock(philo->out);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	if (philo->lim->die == 0)
		end = 1;
	printf("%10.1ld %3.3d %s%s%s\n",
		get_time(philo->lim->start), philo->index + 1, color, str, NRM);
	pthread_mutex_unlock(philo->out);
	return (0);
}

void	forks_move(t_philo *philo, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(philo->left);
		block_print(philo, "has taken a left fork", NRM);
		pthread_mutex_lock(philo->right);
		block_print(philo, "has taken a right fork", NRM);
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
}

void	*life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index % 2 != 0)
		usleep(philo->lim->eat * 0.9 * 1000);
	while (philo->eat != 0)
	{
		forks_move(philo, 0);
		gettimeofday(&philo->hungry, NULL);
		if (block_print(philo, "is eating", GRN) == 1)
			return (NULL);
		usleep(philo->lim->eat * 1000);
		forks_move(philo, 1);
		if (philo->eat > 0)
			philo->eat--;
		if (block_print(philo, "is sleeping", NRM) == 1)
			return (NULL);
		usleep(philo->lim->sleep * 1000);
		if (block_print(philo, "is thinking", YEL) == 1)
			return (NULL);
	}
	return (NULL);
}

int	death_catch(t_all *all)
{
	int		i;
	int		max_i;

	i = 0;
	while (i < all->lim->philo)
	{
		max_i = -1;
		if (get_time(all->philo[i].hungry) > all->lim->die)
		{
			all->lim->die = 0;
			block_print(&all->philo[i], "died", RED);
			return (0);
		}
		if (max_i < all->philo[i].eat)
			max_i = all->philo[i].eat;
		i++;
	}
	usleep(100);
	if (max_i == 0)
	{
		all->lim->die = 0;
		block_print(&all->philo[i - 1], "over on me", BLU);
		return (0);
	}
	return (1);
}

int	start_party(t_all *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->lim->start, NULL);
	while (i < all->lim->philo)
	{
		all->philo[i].hungry = all->lim->start;
		pthread_create(&all->philo[i].ptr, NULL, life, (void *)&all->philo[i]);
		i++;
	}
	i = 0;
	while (death_catch(all) == 1)
		;
	i = 0;
	while (i < all->lim->philo)
	{
		pthread_join(all->philo[i].ptr, NULL);
		i++;
	}
	free(all->philo);
	free(all->fork);
	return (0);
}

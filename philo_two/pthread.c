#include "philo.h"

int	block_print(t_philo *philo, char *str, char *color)
{	
	static char	end;

	if (sem_wait(philo->out))
	{
		philo->lim->error = 1;
		return (1);
	}
	if (end == 1)
		return (left_all(philo));
	if (str[0] == 'd' || str[0] == 'p')
		end = 1;
	if (philo->eat == -1 || str[3] != 'e')
		printf("%10.1ld %3.3d %s%s%s\n",
			get_time(philo->lim->start), philo->index + 1, color, str, NRM);
	else
		printf("%10.1ld %3.3d %s%s (%d)%s\n",
			get_time(philo->lim->start), philo->index + 1, color,
			str, philo->lim->num_eat - philo->eat + 1, NRM);
	if (sem_post(philo->out))
	{
		philo->lim->error = 1;
		return (1);
	}
	return (0);
}

int	forks_move(t_philo *philo, int i)
{
	if (i == 0)
	{
		if (usleep (500) || sem_wait(philo->fork)
			|| block_print(philo, "has taken a fork", NRM)
			|| sem_wait(philo->fork)
			|| block_print(philo, "has taken a fork", NRM))
		{
			philo->lim->error = 1;
			return (1);
		}
	}
	else if (sem_post(philo->fork) || sem_post(philo->fork))
	{
		philo->lim->error = 1;
		return (1);
	}
	return (0);
}

void	*life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (forks_move(philo, 0)
			|| gettimeofday(&philo->hungry, NULL)
			|| block_print(philo, "is eating", GRN)
			|| usleep(philo->lim->eat * 1000)
			|| forks_move(philo, 1))
			return (NULL);
		if (philo->eat > 0)
			philo->eat--;
		if (block_print(philo, "is sleeping", NRM) != 0
			|| usleep(philo->lim->sleep * 1000) != 0
			|| block_print(philo, "is thinking", YEL) != 0)
			return (NULL);
	}
}

int	death_catch(t_all *all)
{
	int		i;
	int		max_eat;

	i = 0;
	max_eat = -1;
	while (i < all->lim->philo)
	{
		if (all->lim->num_eat != -1)
			max_eat = 0;
		if (get_time(all->philo[i].hungry) > all->lim->die)
		{
			block_print(&all->philo[i], "died", RED);
			return (0);
		}
		if (max_eat < all->philo[i].eat)
			max_eat = all->philo[i].eat;
		i++;
	}
	if (max_eat == 0)
	{
		usleep(100);
		block_print(&all->philo[all->lim->philo - 1], "philos are full", BLU);
		return (0);
	}
	return (1);
}

int	start_party(t_all *all)
{
	int	i;

	if (gettimeofday(&all->lim->start, NULL) != 0)
		return (cuba_libre(all, 4, 0));
	i = -1;
	while (++i < all->lim->philo)
	{
		all->philo[i].hungry = all->lim->start;
		if (pthread_create(&all->philo[i].ptr, NULL, life,
				(void *)&all->philo[i]) != 0)
			return (cuba_libre(all, 4, 0));
		usleep(100);
	}
	while (1)
	{
		if (death_catch(all) == 0)
			break ;
		if (all->lim->error == 1)
			return (cuba_libre(all, 4, 0));
		usleep(100);
	}
	i = -1;
	while (++i < all->lim->philo)
		pthread_join(all->philo[i].ptr, NULL);
	return (0);
}

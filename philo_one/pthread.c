#include "philo.h"

int	block_print(t_philo *philo, char *str, char *color)
{	
	static char	end;

	if (ft_mutex(philo, 0) != 0)
		return (1);
	if (end == 1)
	{
		pthread_mutex_unlock(philo->out);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	if (str[0] == 'd' || str[0] == 'p')
		end = 1;
	if (philo->eat == -1 || str[3] != 'e')
		printf("%10.1ld %3.3d %s%s%s\n",
			get_time(philo->lim->start), philo->index + 1, color, str, NRM);
	else
		printf("%10.1ld %3.3d %s%s (%d)%s\n",
			get_time(philo->lim->start), philo->index + 1, color,
			str, philo->lim->num_eat - philo->eat + 1, NRM);
	if (ft_mutex(philo, 1) != 0)
		return (1);
	return (0);
}

int	forks_move(t_philo *philo, int i)
{
	if (i == 0)
	{
		if (pthread_mutex_lock(philo->left) != 0
			|| block_print(philo, "has taken a fork", NRM) != 0
			|| pthread_mutex_lock(philo->right) != 0
			|| block_print(philo, "has taken a fork", NRM) != 0)
		{
			philo->lim->error = 1;
			return (1);
		}
		return (0);
	}
	else
	{
		if (pthread_mutex_unlock(philo->left) != 0
			|| pthread_mutex_unlock(philo->right) != 0)
		{
			philo->lim->error = 1;
			return (1);
		}
		return (0);
	}
}

void	*life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index % 2 != 0)
		usleep(philo->lim->eat * 0.9 * 1000);
	while (1)
	{
		if (forks_move(philo, 0) != 0
			|| gettimeofday(&philo->hungry, NULL) != 0
			|| block_print(philo, "is eating", GRN) != 0
			|| usleep(philo->lim->eat * 1000) != 0
			|| forks_move(philo, 1) != 0)
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
	i = 0;
	while (i < all->lim->philo)
	{
		all->philo[i].hungry = all->lim->start;
		if (pthread_create(&all->philo[i].ptr, NULL, life,
				(void *)&all->philo[i]) != 0)
			return (cuba_libre(all, 4, 0));
		i++;
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

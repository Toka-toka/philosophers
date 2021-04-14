#include "philo.h"

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
		if (philo->eat == 0)
			return (NULL);
		if (block_print(philo, "is sleeping", NRM) != 0
			|| usleep(philo->lim->sleep * 1000) != 0
			|| block_print(philo, "is thinking", YEL) != 0)
			return (NULL);
	}
}

void	death_catch(t_philo *philo)
{
	if (pthread_create(&philo->ptr, NULL, life, (void *)philo))
		exit(2);
	while (1)
	{
		if (get_time(philo->hungry) > philo->lim->die)
		{
			block_print(philo, "died", RED);
			exit (1);
		}
		if (philo->eat == 0)
			exit (0);
		if (philo->lim->error == 1)
			exit (2);
		usleep(1000);
	}
}

void	fork_create(t_all *all)
{
	int	i;

	if (gettimeofday(&all->lim->start, NULL) != 0)
		cuba_libre(all, 4, 0);
	i = -1;
	while (++i < all->lim->philo)
	{
		all->philo[i].hungry = all->lim->start;
		all->philo[i].pid = fork();
		if (all->philo[i].pid == -1)
			cuba_libre(all, 4, 0);
		if (all->philo[i].pid == 0)
			death_catch(&all->philo[i]);
		usleep(100);
	}
}

int	start_party(t_all *all)
{
	int	i;
	int	status;

	fork_create(all);
	i = 0;
	while (i < all->lim->philo)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == 1)
			return (cuba_libre(all, 0, 0));
		else if (status == 2)
			cuba_libre(all, 4, 0);
		i++;
	}
	block_print(&all->philo[all->lim->philo - 1], "philos are full", BLU);
	return (cuba_libre(all, 0, 0));
}

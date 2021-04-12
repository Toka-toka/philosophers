#include "philo.h"

long	get_time(struct timeval p_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000 + time.tv_usec / 1000)
			-(p_time.tv_sec * 1000 + p_time.tv_usec / 1000)));
}

int	init(t_all *all)
{
	int	i;

	i = 0;
	all->philo = malloc(all->lim->philo * sizeof(t_philo));
	all->fork = malloc(all->lim->philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&all->out, NULL);
	while (i < all->lim->philo)
	{
		pthread_mutex_init(&all->fork[i], NULL);
		all->philo[i].lim = all->lim;
		all->philo[i].out = &all->out;
		all->philo[i].index = i;
		all->philo[i].left = &all->fork[i];
		all->philo[i].eat = all->lim->num_eat;
		if (i != 0)
			all->philo[i].right = &all->fork[i - 1];
		i++;
	}
	all->philo[0].right = &all->fork[i - 1];
	return (0);
}

int	pars_argv(int i, int value, t_all *all)
{
	if (i == 1)
		all->lim->philo = value;
	else if (i == 2)
		all->lim->die = value;
	else if (i == 3)
		all->lim->eat = value;
	else if (i == 4)
		all->lim->sleep = value;
	else if (i == 5)
		all->lim->num_eat = value;
	if (all->lim->philo <= 1 || all->lim->philo > 200
		|| all->lim->die < 60 || all->lim->eat < 60 || all->lim->sleep < 60)
		return (1);
	else
		return (0);
}

int	check_argv(char **argv, t_all *all)
{
	int		i;
	int		value;
	char	*temp;
	int		status;

	i = 1;
	while (argv[i] != NULL)
	{
		status = 0;
		value = ft_atoi(argv[i]);
		temp = ft_itoa(value);
		if (ft_strncmp(argv[i], temp, ft_strlen(argv[i])) != 0 || value <= 0)
			status = 1;
		else if (pars_argv(i, value, all) != 0)
			status = 2;
		free(temp);
		if (status == 0 && i++)
			continue ;
		else if (status == 1)
			printf("%d argument is invalid\n", i);
		else if (status == 2)
			printf("%d argument is out of rulls of simulation\n", i);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	t_lim	lim;

	all.lim = &lim;
	all.lim->philo = 2;
	all.lim->die = 60;
	all.lim->eat = 60;
	all.lim->sleep = 60;
	all.lim->num_eat = -1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	if (check_argv(argv, &all) != 0)
		return (1);
	init(&all);
	start_party(&all);
	return (0);
}

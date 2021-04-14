#include "philo.h"

int	cuba_libre(t_all *all, int status, int i)
{
	int	j;

	j = -1;
	if (all->philo != NULL)
	{
		while (++j < all->lim->philo)
			kill(all->philo[i].pid, SIGKILL);
		free(all->philo);
		all->philo = NULL;
	}
	sem_close(all->out);
	sem_close(all->fork);
	if (status == 0)
		return (0);
	else if (status == 1)
		printf("%sInvalid number of arguments\n%s", RED, WHT);
	else if (status == 2)
		printf("%s%d argument is invalid\n%s", RED, i, WHT);
	else if (status == 3)
		printf("%s%d argument is out of rulls of simulation\n%s", RED, i, WHT);
	else if (status == 4)
		printf("%sFatal error\n%s", RED, WHT);
	exit (1);
}

int	init(t_all *all)
{
	int	i;

	i = 0;
	all->philo = malloc(all->lim->philo * sizeof(t_philo));
	sem_unlink("/fork");
	sem_unlink("/out");
	all->fork = sem_open("/fork", O_CREAT, 0666, all->lim->philo);
	all->out = sem_open("/out", O_CREAT, 0666, 1);
	if (all->fork == SEM_FAILED || all->out == SEM_FAILED
		|| all->philo == NULL)
		return (cuba_libre(all, 4, 0));
	while (i < all->lim->philo)
	{
		all->philo[i].lim = all->lim;
		all->philo[i].out = all->out;
		all->philo[i].fork = all->fork;
		all->philo[i].index = i;
		all->philo[i].eat = all->lim->num_eat;
		i++;
	}
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
		if (temp == NULL)
			return (cuba_libre(all, 4, 0));
		if (ft_strncmp(argv[i], temp, ft_strlen(argv[i])) != 0
			|| value <= 0)
			status = 2;
		else if (pars_argv(i, value, all) != 0)
			status = 3;
		free(temp);
		if (status != 0)
			return (cuba_libre(all, status, i));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	t_lim	lim;

	all.lim = &lim;
	all.philo = NULL;
	all.lim->philo = 2;
	all.lim->die = 60;
	all.lim->eat = 60;
	all.lim->sleep = 60;
	all.lim->num_eat = -1;
	all.lim->error = 0;
	if (argc < 5 || argc > 6)
		return (cuba_libre(&all, 1, 0));
	if (check_argv(argv, &all)
		|| init(&all)
		|| start_party(&all))
		return (1);
	return (cuba_libre(&all, 0, 0));
}

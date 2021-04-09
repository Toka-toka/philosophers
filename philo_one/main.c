#include "philo.h"

/*
void	waid(useconds_t time)
{
	useconds_t		end;
	struct timeval	get_time;

	end = 0;
	while ((time - end) > 0)
	{
		usleep(10);
		gettimeofday(&get_time, NULL);
		end = get_time.tv_sec * 1000 + get_time.tv_usec / 1000;
	}
}*/

void	*work(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->mutex);
	printf("Hello, im philo №%d\n", philo->number);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	start_party(t_all *all)
{
	int	i;
	
	i = 0;
	while (i < all->lim->philo)
	{
		if (i % 2 == 0)
		{
			pthread_create(&all->philo_ptr[i].ptr, NULL, life,
				(void *)&all->philo_ptr[i]);
			i++;
		}
	}
	i = 0;
	while (i < all->lim->philo)
	{
		if (i % 2 != 0)
		{
			pthread_create(&all->philo_ptr[i].ptr, NULL, life,
				(void *)&all->philo_ptr[i]);
			i++;
		}
	}
	pthread_create(&all->wizard, NULL, death_catch,(void *)&all->philo_ptr[i]);
	pthread_join(all->wizard, NULL);
	return (0);
}

int		init(t_all *all)
{
	int	i;
	
	i = 0;
	all->philo_ptr = malloc(all->lim->philo * sizeof(t_philo));
	while (i < all->lim->philo)
	{
		all->philo_ptr[i].number = i;
		all->philo_ptr[i].input = &all->input;
		i++;
	}
}
/*
void	create_phylo(t_all *all)
{
	int	i;

	i = 0;
	all->philo_ptr = malloc(all->lim->philo * sizeof(t_philo));
	while (i < all->lim->philo)
	{
		all->philo_ptr[i].number = i;
		all->philo_ptr[i].mutex = &all->mutex;

	}
}*/

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
	if (all->lim->philo < 1 || all->lim->philo > 200
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
			continue;
		else if (status == 1)
			printf("%d argument is invalid\n", i);
		else if (status == 2)
			printf("%d argument is out of rulls of simulation\n", i);
		return(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	t_lim	lim;

	all.lim = &lim;
	lim.philo = 2;
	lim.die = 60;
	lim.eat = 60;
	lim.sleep = 60;
	lim.num_eat = -1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return(1);
	}
	if(check_argv(argv, &all) != 0)
		return(1);
	init(all);
	gettimeofday(&all.start, NULL);

	(end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000)); */
	return(0);
}
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

void	create_phylo(t_all *all)
{
	int	i;

	i = 0;
	all->philo_ptr = malloc(all->philo_num * sizeof(t_philo));
	while (i < all->philo_num)
	{
		all->philo_ptr[i].number = i;
		all->philo_ptr[i].mutex = &all->mutex;
		pthread_create(&all->philo_ptr[i].ptr, NULL, work,
			(void *)&all->philo_ptr[i]);
		i++;
	}
}

int	pars_argv(int i, int value, t_all *all)
{
	if (i == 1)
		all->philo_num = value;
	else if (i == 2)
		all->die_speed = value;
	else if (i == 3)
		all->eat_speed = value;
	else if (i == 4)
		all->sleep_speed = value;
	else if (i == 5)
		all->times_eat = value;
	if (all->philo_num < 1 || all->philo_num > 200 || all->die_speed < 60 || all->eat_speed < 60 || all->sleep_speed < 60)
		return (1);
	else
		return (0);
}

int	check_argv(char **argv, t_all *all)
{
	int		i;
	int		value;
	char	*temp;

	i = 1;
	while (argv[i] != NULL)
	{
		value = ft_atoi(argv[i]);
		temp = ft_itoa(value);
		if (ft_strncmp(argv[i], temp, ft_strlen(argv[i])) != 0 || value <= 0)
		{
			free(temp);
			printf("%d argument is invalid \n", i);
			return (1);
		}
		if (pars_argv(i, value, all) != 0)
		{
			printf("%d argument is out of rulls of simulation\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
//	struct timeval start, end;
	t_all	all;
/*    int i;

	i = 0;
	all.philo_num = 100000;
	pthread_mutex_init(&all.mutex, NULL);
	create_phylo(&all);
	while (i < all.philo_num)
	{
		pthread_join(all.philo_ptr[i].ptr, NULL);
		i++;
	}*/	
	all.philo_num = 2;
	all.die_speed = 60;
	all.eat_speed = 60;
	all.sleep_speed = 60;
	all.times_eat = -1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return(1);
	}
	if(check_argv(argv, &all) != 0)
		return(1);
/*	gettimeofday(&start, NULL);
	usleep(10000*1000);
//    waid(1000*1000); // микро
	gettimeofday(&end, NULL);
	printf("%ld mill seconds\n",
	(end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000)); */
	return(0);
}
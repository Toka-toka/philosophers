#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	block_print(t_philo *philo, char *str, char *color)
{	
	if (sem_wait(philo->out))
	{
		philo->lim->error = 1;
		return (1);
	}
	if (philo->eat == -1 || str[3] != 'e')
		printf("%10.1ld %3.3d %s%s%s\n",
			get_time(philo->lim->start), philo->index + 1, color, str, NRM);
	else
		printf("%10.1ld %3.3d %s%s (%d)%s\n",
			get_time(philo->lim->start), philo->index + 1, color,
			str, philo->lim->num_eat - philo->eat + 1, NRM);
	if (str[0] == 'd')
		return (1);
	if (sem_post(philo->out))
	{
		philo->lim->error = 1;
		return (1);
	}
	return (0);
}

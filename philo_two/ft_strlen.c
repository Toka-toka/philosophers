#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	left_all(t_philo *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
	sem_post(philo->out);
	return (1);
}

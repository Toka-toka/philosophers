#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	ft_mutex(t_philo *philo, int i)
{
	if (i == 0)
	{
		if (pthread_mutex_lock(philo->out) != 0)
		{
			philo->lim->error = 1;
			return (1);
		}
		return (0);
	}
	else if (i == 1)
	{
		if (pthread_mutex_unlock(philo->out) != 0)
		{
			philo->lim->error = 1;
			return (1);
		}
	}
	return (0);
}

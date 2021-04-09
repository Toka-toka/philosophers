#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				flag;
	unsigned long	number;

	i = 0;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	flag = (*str == 45 ? -1 : 1);
	if (*str == 43 || *str == 45)
		str++;
	while (*str == 48)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		number = *str - 48 + number * 10;
		i++;
		str++;
	}
	if (number > 9223372036854775807 || i >= 20)
		return (-0.5 * (flag + 1));
	return (number * flag);
}

char		*ft_itoa(int n)
{
	int				i;
	char			*str;
	unsigned int	number;

	i = n > 0 ? 0 : 1;
	number = n >= 0 ? n : -n;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[0] = number != 0 ? '-' : '0';
	str[i] = '\0';
	while (number != 0)
	{
		str[--i] = number % 10 + 48;
		number = number / 10;
	}
	return (str);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	i = 0;
	str1 = (char*)s1;
	str2 = (char*)s2;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
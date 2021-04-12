#ifndef PHILO_H

# define PHILO_H

# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_lim
{
	struct timeval	start;
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				num_eat;
}				t_lim;

typedef struct s_philo
{
	int				index;
	int				eat;
	pthread_t		ptr;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*out;
	struct timeval	hungry;
	t_lim			*lim;
}				t_philo;

typedef struct s_all
{
	t_philo			*philo;
	pthread_t		wizard;
	pthread_mutex_t	out;
	pthread_mutex_t	*fork;
	t_lim			*lim;
}				t_all;

int		start_party(t_all *all);
long	get_time(struct timeval p_time);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif
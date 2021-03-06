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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_lim
{
	struct timeval	start;
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				num_eat;
	int				error;
}				t_lim;

typedef struct s_philo
{
	int				index;
	pid_t			pid;
	int				eat;
	pthread_t		ptr;
	sem_t			*out;
	sem_t			*fork;
	struct timeval	hungry;
	t_lim			*lim;
}				t_philo;

typedef struct s_all
{
	t_philo			*philo;
	sem_t			*out;
	sem_t			*fork;
	t_lim			*lim;
}				t_all;

int		cuba_libre(t_all *all, int status, int i);
int		start_party(t_all *all);
long	get_time(struct timeval p_time);
int		left_all(t_philo *philo);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_mutex(t_philo *philo, int i);
int		block_print(t_philo *philo, char *str, char *color);

#endif
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct	s_lim
{
	struct timeval	start;
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				num_eat;
}				t_lim;

typedef struct	s_philo
{
	int             number;
	pthread_t		ptr; 
	pthread_mutex_t	*input;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_lim			*lim;
	struct timeval	hungry;
	pthread_mutex_t	*out;
/*	struct timeval	start;
	struct timeval	t_die;
	t_forks			*left;
	t_forks			*right;
	int				index;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count_eat;
	int				is_stop;*/
}				t_philo;

typedef struct	s_all
{
	struct timeval	start;
//	t_forks			*forks;
	t_philo			*philo_ptr;
	pthread_t		wizard;
    pthread_mutex_t	out;
	pthread_mutex_t *fork;
	t_lim			*lim;
/*	pthread_t		checker;
	pthread_mutex_t	display; */
}				t_all;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
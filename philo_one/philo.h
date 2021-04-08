#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct	s_philo
{
	pthread_t		ptr;
    int             number;
	pthread_mutex_t	*mutex;
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
	int				philo_num;
//	t_forks			*forks;
	t_philo			*philo_ptr;
    pthread_mutex_t	mutex;
/*	pthread_t		checker;
	pthread_mutex_t	display; */
}				t_all;
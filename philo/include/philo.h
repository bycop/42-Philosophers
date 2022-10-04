/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 03:43:04 by bycop          #+#    #+#             */
/*   Updated: 2021/06/29 13:31:03 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define LST_ARG "Error Argument: philo_number time_to_die time_to_eat \
time_to_sleep [must_eat]"

typedef struct s_global
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead_numb;
	int				done;
	int				start;
	pthread_t		id;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	done_mutex;
	pthread_mutex_t	dead;
}					t_global;

typedef struct s_thread
{
	t_global		*g;
	int				id;
	int				eat;
	pthread_t		thread;
	pthread_mutex_t	timemutex;
	struct timeval	last_meal;
}				t_thread;

/*
**	INIT
*/

int		init(t_global *g, int ac, char **av);
int		number_only(int ac, char **av);
void	global_init(t_global *g, int i, int *p_i);
int		free_end(t_global *g, t_thread *philo, int type);

/*
**	PRINTERS
*/

void	print_sleep(t_thread *thread);
void	print_eat(t_thread *thread);
void	print_think(t_thread *thread);
void	*print_end(t_thread *thread);
void	print_fork(t_thread *thread);

/*
**	UTILS
*/

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		time_now(void);
int		thread_zero(t_thread *thread);

#endif
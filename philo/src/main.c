/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 03:42:51 by bycop          #+#    #+#             */
/*   Updated: 2021/06/30 19:18:23 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threadFunc(void *arg)
{
	t_thread	*thread;

	thread = arg;
	thread->eat = 0;
	gettimeofday(&thread->last_meal, NULL);
	while (42)
	{
		pthread_mutex_lock(&thread->g->forks_mutex[thread_zero(thread)]);
		print_fork(thread);
		pthread_mutex_lock(&thread->g->forks_mutex[thread->id - 1]);
		print_fork(thread);
		pthread_mutex_lock(&thread->timemutex);
		gettimeofday(&thread->last_meal, NULL);
		pthread_mutex_unlock(&thread->timemutex);
		print_eat(thread);
		if (thread->g->must_eat != -1 && thread->eat == thread->g->must_eat)
			return (print_end(thread));
		print_sleep(thread);
		print_think(thread);
	}
	return (print_end(thread));
}

void	while_check(t_global *g, t_thread *philo)
{
	int				j;
	struct timeval	now;

	j = 0;
	usleep(2000);
	while (j < g->philo_number)
	{
		pthread_mutex_lock(&philo[j].timemutex);
		gettimeofday(&now, NULL);
		if ((now.tv_sec * 1000 + now.tv_usec / 1000)
			- (philo[j].last_meal.tv_sec * 1000
				+ philo[j].last_meal.tv_usec / 1000) > g->time_to_die)
		{
			pthread_mutex_lock(&g->print_mutex);
			pthread_mutex_lock(&g->dead);
			g->dead_numb = philo[j].id;
			break ;
		}
		pthread_mutex_unlock(&philo[j].timemutex);
		j++;
	}
}

int	main(int ac, char **av)
{
	t_global	g;
	t_thread	*philo;
	int			i;
	int			err;

	if (init(&g, ac, av))
		return (1);
	philo = malloc(sizeof(t_thread) * g.philo_number);
	g.forks_mutex = malloc(sizeof(pthread_mutex_t) * (g.philo_number));
	if (philo == NULL || g.forks_mutex == NULL)
		exit(free_end(&g, philo, 2));
	global_init(&g, 0, &i);
	while (++i < g.philo_number)
	{
		philo[i].g = &g;
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].timemutex, NULL);
		err = pthread_create(&philo[i].thread, NULL, &threadFunc, &philo[i]);
		if (err)
			exit(free_end(&g, philo, 1));
		usleep(100);
	}
	while (42 && !g.dead_numb && g.done < g.philo_number)
		while_check(&g, philo);
	exit(free_end(&g, philo, 0));
}

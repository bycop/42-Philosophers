/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 03:42:56 by bycop          #+#    #+#             */
/*   Updated: 2021/06/30 20:19:29 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	number_only(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (ft_isdigit(av[i][j]))
			j++;
		if (av[i][j])
			return (1);
		i++;
	}
	return (0);
}

int	init(t_global *g, int ac, char **av)
{
	if (ac < 5 || ac > 6 || number_only(ac, av))
		return (printf(LST_ARG));
	g->forks_mutex = NULL;
	g->philo_number = ft_atoi(av[1]);
	g->time_to_die = ft_atoi(av[2]);
	g->time_to_eat = ft_atoi(av[3]);
	g->time_to_sleep = ft_atoi(av[4]);
	if (g->philo_number <= 0 || g->time_to_die < 60 || g->time_to_eat < 60
		|| g->time_to_sleep < 60 || g->philo_number > 200)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) > 0)
		g->must_eat = ft_atoi(av[5]);
	else
		g->must_eat = -1;
	return (0);
}

void	global_init(t_global *g, int i, int *p_i)
{
	while (i < g->philo_number)
		pthread_mutex_init(&g->forks_mutex[i++], NULL);
	pthread_mutex_init(&g->dead, NULL);
	pthread_mutex_init(&g->done_mutex, NULL);
	pthread_mutex_init(&g->print_mutex, NULL);
	*p_i = -1;
	g->dead_numb = 0;
	g->start = time_now();
}

int	free_end(t_global *g, t_thread *philo, int type)
{
	int	i;

	i = 0;
	if (g->dead_numb)
		printf("\e[91m%d \e[0m| Thread %d died 💀\n", time_now()
			- g->start, g->dead_numb);
	if (type > 0)
		printf("Error Exiting(1)\n");
	if (type == 2)
		return (1);
	while (i < g->philo_number)
	{
		pthread_mutex_destroy(&g->forks_mutex[i]);
		pthread_mutex_destroy(&philo[i++].timemutex);
	}
	pthread_mutex_destroy(&g->dead);
	pthread_mutex_destroy(&g->done_mutex);
	pthread_mutex_destroy(&g->print_mutex);
	free(g->forks_mutex);
	free(philo);
	return (type);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 03:42:53 by bycop          #+#    #+#             */
/*   Updated: 2021/06/29 13:33:56 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_sleep(t_thread *thread)
{
	pthread_mutex_lock(&thread->g->print_mutex);
	printf("\e[91m%d \e[0m| Thread %d is sleeping 💤\n", time_now()
		- thread->g->start, thread->id);
	pthread_mutex_unlock(&thread->g->print_mutex);
	usleep(thread->g->time_to_sleep * 1000);
}

void	print_fork(t_thread *thread)
{
	pthread_mutex_lock(&thread->g->print_mutex);
	printf("\e[91m%d \e[0m| Thread %d has taken a fork 🍴\n", time_now()
		- thread->g->start, thread->id);
	pthread_mutex_unlock(&thread->g->print_mutex);
}

void	print_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->g->print_mutex);
	printf("\e[91m%d \e[0m| Thread %d is eating 🍝\n", time_now()
		- thread->g->start, thread->id);
	pthread_mutex_unlock(&thread->g->print_mutex);
	usleep(thread->g->time_to_eat * 1000);
	thread->eat++;
	pthread_mutex_unlock(&thread->g->forks_mutex[thread->id - 1]);
	pthread_mutex_unlock(&thread->g->forks_mutex[thread_zero(thread)]);
}

void	print_think(t_thread *thread)
{
	pthread_mutex_lock(&thread->g->print_mutex);
	printf("\e[91m%d \e[0m| Thread %d is thinking 💭\n", time_now()
		- thread->g->start, thread->id);
	pthread_mutex_unlock(&thread->g->print_mutex);
}

void	*print_end(t_thread *thread)
{
	pthread_mutex_lock(&thread->g->done_mutex);
	thread->g->done += 1;
	pthread_mutex_unlock(&thread->g->done_mutex);
	pthread_mutex_lock(&thread->g->print_mutex);
	printf("\e[91m%d \e[0m| Thread %d is finished ✔️\n", time_now()
		- thread->g->start, thread->id);
	pthread_mutex_unlock(&thread->g->print_mutex);
	return (NULL);
}

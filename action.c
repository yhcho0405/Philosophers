/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:13:19 by youncho           #+#    #+#             */
/*   Updated: 2021/07/13 23:40:48 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->info->forks[p->l_fork]);
	print_state(p, TAKE_FORK);
	pthread_mutex_lock(&p->info->forks[p->r_fork]);
	print_state(p, TAKE_FORK);
}

void	philo_eating(t_philo *p)
{
	if (p->info->is_run <= 0)
		return ;
	philo_take_fork(p);
	pthread_mutex_lock(&p->mutex);
	p->last_eat = get_time_ms();
	print_state(p, EAT);
	p->noe--;
	if (!p->noe)
		p->info->is_run--;
	usleep(p->info->tte * 1000);
	pthread_mutex_unlock(&p->mutex);
}

void	philo_sleeping(t_philo *p)
{
	if (p->info->is_run <= 0)
		return ;
	print_state(p, SLEEP);
	pthread_mutex_unlock(&p->info->forks[p->l_fork]);
	pthread_mutex_unlock(&p->info->forks[p->r_fork]);
	usleep(p->info->tts * 1000);
}

void	philo_thinking(t_philo *p)
{
	if (p->info->is_run <= 0)
		return ;
	print_state(p, THINK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:13:19 by youncho           #+#    #+#             */
/*   Updated: 2021/07/14 15:54:28 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->info->forks[p->l_fork]);
	print_state(p, TAKE_FORK, get_time_ms());
	pthread_mutex_lock(&p->info->forks[p->r_fork]);
	print_state(p, TAKE_FORK, get_time_ms());
}

void	philo_eating(t_philo *p)
{
	uint64_t	real_time;

	philo_take_fork(p);
	real_time = get_time_ms();
	pthread_mutex_lock(&p->mutex);
	if (p->info->is_run <= 0)
		return ;
	print_state(p, EAT, real_time);
	p->last_eat = real_time;
	p->noe--;
	if (!p->noe)
		p->info->is_run--;
	pthread_mutex_unlock(&p->mutex);
	mysleep(p->info->tte, p);
}

void	philo_sleeping(t_philo *p, uint64_t real_time)
{
	if (p->info->is_run <= 0)
		return ;
	pthread_mutex_unlock(&p->info->forks[p->l_fork]);
	pthread_mutex_unlock(&p->info->forks[p->r_fork]);
	print_state(p, SLEEP, real_time);
	mysleep(p->info->tts, p);
}

void	philo_thinking(t_philo *p, uint64_t real_time)
{
	if (p->info->is_run <= 0)
		return ;
	print_state(p, THINK, real_time);
}

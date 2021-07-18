/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:40:40 by youncho           #+#    #+#             */
/*   Updated: 2021/07/18 21:46:09 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*survive_check_loop(void *pv)
{
	t_philo *p;

	p = pv;
	while (1)
	{
		pthread_mutex_lock(&p->mutex);
		if (get_time_ms() - p->last_eat > p->info->ttd)
		{
			print_state(p, DIE, get_time_ms());
			pthread_mutex_unlock(&p->mutex);
			return (0);
		}
		pthread_mutex_unlock(&p->mutex);
		usleep(100);
	}
}

void	*life_cycle_loop(void *pv)
{
	pthread_t	tid;
	t_philo *p;

	p = pv;
	p->last_eat = get_time_ms();
	if (pthread_create(&tid, NULL, &survive_check_loop, p))
		return ((void *)1);
	pthread_detach(tid);
	if (p->name % 2 == 0)
		mysleep(p->info->tte * 0.5, p);
	while (p->info->is_run > 0)
	{
		philo_eating(p);
		philo_sleeping(p, get_time_ms());
		philo_thinking(p, get_time_ms());
	}
	return (0);
}

int	philosophers_init(t_info *info, int argc, int i)
{
	info->philos = malloc(sizeof(t_philo) * info->nop);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nop);
	if (!info->philos || !info->forks || info->nop < 2 || info->ttd < 30
		|| info->tte < 30 || info->tts < 30 || (argc == 6 && info->noe < 1))
		return (FAIL);
	pthread_mutex_init(&info->write, NULL);
	while (++i < info->nop)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].mutex, NULL);
		info->philos[i].info = info;
		info->philos[i].name = i + 1;
		info->philos[i].l_fork = i;
		info->philos[i].r_fork = (i + 1) % info->nop;
		info->philos[i].noe = info->noe;
	}
	i = 0;
	info->start_time = get_time_ms();
	while (i < info->nop && !pthread_create(&info->philos[i].thread, NULL,
						life_cycle_loop, &info->philos[i])
						&& !pthread_detach(info->philos[i++].thread))
		usleep(10);
	if (i != info->nop)
		return (FAIL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (1);
	info.nop = atoi_positive(argv[1]);
	info.ttd = atoi_positive(argv[2]);
	info.tte = atoi_positive(argv[3]);
	info.tts = atoi_positive(argv[4]);
	info.noe = -1;
	if (argc == 6)
		info.noe = atoi_positive(argv[5]);
	info.is_run = info.nop;
	if (philosophers_init(&info, argc, -1) == FAIL)
		return (1);
	while (info.is_run)
		;
	exit_phase(&info);
	return (0);
}

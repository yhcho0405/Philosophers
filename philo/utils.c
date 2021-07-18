/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:30:39 by youncho           #+#    #+#             */
/*   Updated: 2021/07/18 21:46:12 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
**	< atoi_positive >
**
**	IF atoi_result == positive number(1 ~ INT_MAX)
**		RETURN atoi_result
**	ELSE
**		RETURN 0
*/
int	atoi_positive(const char *str)
{
	uint64_t	ans;
	size_t		len;

	ans = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if ((*str == '-' || *str == '+') && *(str++) == '-')
		return (0);
	len = 0;
	while (str[len])
		len++;
	if (len > 10 || len == 0)
		return (0);
	while ('0' <= *str && *str <= '9')
		ans = ans * 10 + *(str++) - '0';
	if (*str || (int64_t)INT_MAX < (int64_t)ans)
		return (0);
	return (ans);
}

uint64_t	get_time_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print_state(t_philo *p, int state, uint64_t real_time)
{
	const char	*str[6] =
		{STR_TAKE_FORK, STR_EAT, STR_SLEEP, STR_THINK, STR_DIE, NULL};

	pthread_mutex_lock(&p->info->write);
	if (p->info->is_run > 0)
		printf("%llu %d %s",
			real_time - p->info->start_time, p->name, str[state]);
	if (state == DIE)
		p->info->is_run = 0;
	pthread_mutex_unlock(&p->info->write);
}

void	mysleep(uint64_t sleep_ms, t_philo *p)
{
	uint64_t	end_time;

	end_time = get_time_ms() + sleep_ms;
	while (get_time_ms() < end_time && p->info->is_run)
		usleep(100);
}

void	exit_phase(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nop)
		pthread_mutex_destroy(&info->forks[i]);
	free(info->forks);
	i = -1;
	while (++i < info->nop)
		pthread_mutex_destroy(&info->philos[i].mutex);
	free(info->philos);
	pthread_mutex_destroy(&info->write);
}

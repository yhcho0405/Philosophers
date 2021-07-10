/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:40:40 by youncho           #+#    #+#             */
/*   Updated: 2021/07/11 03:24:23 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philosophers_init(int argc, char **argv, t_info *info)
{
	info->nop = atoi_positive(argv[1]);
	info->ttd = atoi_positive(argv[2]);
	info->tte = atoi_positive(argv[3]);
	info->tts = atoi_positive(argv[4]);
	info->noe = 0;
	if (argc == 6)
		info->noe = atoi_positive(argv[5]);
	info->philos = malloc(sizeof(t_philo) * info->nop);
	if (!info->philos || info->nop < 2 || info->ttd < 30 || info->tte < 30
		|| info->tts < 30 || (argc == 6 && info->noe < 30))
		return (FAIL);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nop);
	if (!info->forks)
		return (FAIL);
	//TODO: mutex init
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (1);
	if (philosophers_init(argc, argv, &info) == FAIL)
		return (1);
	return (0);
}

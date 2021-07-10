/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:41:07 by youncho           #+#    #+#             */
/*   Updated: 2021/07/11 03:19:54 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define FAIL		0
# define SUCCESS	1

typedef struct s_philo
{

}	t_philo;

/*
**	abbr.
**
**	nop	->	number_of_philosophers
**	ttd	->	time_to_die
**	tte	->	time_to_eat
**	tts	->	time_to_sleep
**	noe	->	number_of_times_each_philosopher_must_eat (optional)
*/
typedef struct s_info
{
	uint64_t		start_time;
	int				nop;
	uint32_t		ttd;
	uint32_t		tte;
	uint32_t		tts;
	int				noe;
	t_philo 		*philos;
	pthread_mutex_t *forks;
}	t_info;

/*
**	utils.c
*/
int	atoi_positive(const char *str);

#endif

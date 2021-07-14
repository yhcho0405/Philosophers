/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:41:07 by youncho           #+#    #+#             */
/*   Updated: 2021/07/14 15:17:13 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define FAIL		0
# define SUCCESS	1

# define TAKE_FORK	0
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4


# define STR_TAKE_FORK	"has taken a fork\n"
# define STR_EAT 		"is eating\n"
# define STR_SLEEP		"is sleeping\n"
# define STR_THINK		"is thinking\n"
# define STR_DIE		"died\n"

typedef struct s_info	t_info;

/*
**	abbr.
**
**	nop	->	number_of_philosophers
**	ttd	->	time_to_die
**	tte	->	time_to_eat
**	tts	->	time_to_sleep
**	noe	->	number_of_times_each_philosopher_must_eat (optional)
*/
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_info			*info;
	int				name;
	int				l_fork;
	int				r_fork;
	int				noe;
	uint64_t		last_eat;
}	t_philo;

typedef struct s_info
{
	uint64_t		start_time;
	int				nop;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	int				noe;
	int				is_run;
	t_philo 		*philos;
	pthread_mutex_t *forks;
	pthread_mutex_t	write;
}	t_info;

/*
**	action.c
*/
void		philo_eating(t_philo *p);
void		philo_sleeping(t_philo *p, uint64_t real_time);
void		philo_thinking(t_philo *p, uint64_t real_time);

/*
**	utils.c
*/
int			atoi_positive(const char *str);
uint64_t	get_time_ms(void);
void		print_state(t_philo *p, int state, uint64_t real_time);
void		mysleep(uint64_t time, t_philo *p);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:41:07 by youncho           #+#    #+#             */
/*   Updated: 2021/07/23 13:30:22 by youncho          ###   ########.fr       */
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

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define COLOR_PRINT	1

# if COLOR_PRINT
#  define STR_TAKE_FORK	"\x1b[32mhas taken a fork\n\x1b[0m"
#  define STR_EAT		"\x1b[33mis eating\n\x1b[0m"
#  define STR_SLEEP		"\x1b[36mis sleeping\n\x1b[0m"
#  define STR_THINK		"\x1b[34mis thinking\n\x1b[0m"
#  define STR_DIE		"\x1b[31mdied\n\x1b[0m"
# else
#  define STR_TAKE_FORK	"has taken a fork\n"
#  define STR_EAT 		"is eating\n"
#  define STR_SLEEP		"is sleeping\n"
#  define STR_THINK		"is thinking\n"
#  define STR_DIE		"died\n"
# endif

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
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_info;

/*
**	philosophers.c
*/
void		*survive_check_loop(void *pv);
void		*life_cycle_loop(void *pv);
int			philosophers_init(t_info *info, int argc, int i);

/*
**	actions.c
*/
void		philo_take_fork(t_philo *p);
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
void		exit_phase(t_info *info);

#endif

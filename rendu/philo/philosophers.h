/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:03:54 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 21:03:37 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum	e_state
{
	THINKING,
	EATING,
	SLEEPING
};

enum	e_message
{
	DIED,
	LFORK,
	RFORK,
	EAT,
	SLEEP,
	THINK,
	ARG
};

typedef struct s_params
{
	int				nb_of_philo;
	int				ms_to_die;
	int				ms_to_eat;
	int				ms_to_sleep;
	int				nb_times_each_eat;
	int				nb_philo_unrested;
	int				valid;
	int				check_eat;
	long long		top_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	global_mutex;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				state;
	int				died;
	int				elapsed_time;
	int				finish_eating;
	int				nb_eat;
	long long		start_time;
	t_params		*params;
	pthread_t		thread;
	pthread_t		death;
	pthread_mutex_t	eat_die_mutex;
	pthread_mutex_t	left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	struct s_philo	*next;
}	t_philo;

void		lunch_philo(t_params *params, t_philo *philo);
int			create_linked_philos(t_params *params, t_philo *philo);
int			init_philo(t_params *params, t_philo *start, \
t_philo *tmp_philo, int id);
int			create_threads(t_params *params, t_philo *philo);
int			starting_threads(t_params *params, t_philo *tmp_philo, int i);
void		*death_thread(void *arg);
void		*philo_thread(void *arg);
int			check_rested_philo(t_philo *tmp);
void		thinking_state(t_philo *tmp);
void		eating_state(t_philo *tmp);
void		sleeping_state(t_philo *tmp);
void		display_log(t_params *params, t_philo *philo, int err);
void		print_message(t_params *params, t_philo *philo, int err);
int			set_args(int argc, char **argv, t_params	*params);
void		free_mutexes(t_philo *philo, t_params *params);
int			atoi_lite(const char *str);
long long	ft_get_time(void);
long long	elapsed_ms(long long start, long long end);
int			ft_wait_timer_ms(long timerms);

#endif

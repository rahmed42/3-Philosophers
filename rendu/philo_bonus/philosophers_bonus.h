/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:03:54 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 20:30:32 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

enum	e_state
{
	THINKING,
	EATING,
	SLEEPING
};

enum	e_type
{
	CREATE,
	DESTROY
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
	int				valid;
	int				check_eat;
	long long		top_time;
	sem_t			*sem_print;
	sem_t			*sem_eat_die;
	sem_t			*sem_forks;
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
	char			*name;
	t_params		*params;
	pthread_t		death;
}	t_philo;

void		create_philos(t_params *params, t_philo *philo);
void		launch_philo(t_params *params, t_philo *philo, pid_t *pid);
void		wait_processes(t_params *params);
void		sem_eat_die_name(t_philo *tmp, int type);
int			create_threads(t_philo *philo);
void		*death_thread(void *arg);
void		philo_process(t_philo *tmp);
int			check_rested_philo(t_philo *tmp);
void		eating_state(t_philo *tmp);
void		sleeping_state(t_philo *tmp);
void		thinking_state(t_philo *tmp);
void		display_log(t_params *params, t_philo *philo, int err);
void		print_message(t_params *params, t_philo *philo, int err);
int			set_args(int argc, char **argv, t_params	*params);
void		free_semaphores(t_philo *philo, t_params *params, pid_t *pid);
long long	ft_get_time(void);
long long	elapsed_ms(long long start, long long end);
int			ft_wait_timer_ms(long timerms);
int			atoi_lite(const char *str);
char		*ft_itoa_lite(int n);
char		*ft_strjoin_del_str2(char const *s1, char *s2);
size_t		ft_strlen(const char *s);

#endif

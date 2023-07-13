/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:20:18 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 20:55:37 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_rested_philo(t_philo *tmp)
{
	if (tmp->params->check_eat && \
	(tmp->nb_eat >= tmp->params->nb_times_each_eat))
	{
		pthread_mutex_lock(&tmp->params->global_mutex);
		--tmp->params->nb_philo_unrested;
		tmp->finish_eating = 1;
		pthread_mutex_unlock(&tmp->params->global_mutex);
		return (1);
	}
	return (0);
}

void	eating_state(t_philo *tmp)
{
	tmp->state = EATING;
	pthread_mutex_lock(&tmp->left_fork_mutex);
	display_log(tmp->params, tmp, LFORK);
	pthread_mutex_lock(tmp->right_fork_mutex);
	display_log(tmp->params, tmp, RFORK);
	tmp->start_time = ft_get_time();
	pthread_mutex_lock(&tmp->eat_die_mutex);
	display_log(tmp->params, tmp, EAT);
	ft_wait_timer_ms(tmp->params->ms_to_eat);
	tmp->nb_eat++;
	pthread_mutex_unlock(&tmp->eat_die_mutex);
	pthread_mutex_unlock(&tmp->left_fork_mutex);
	pthread_mutex_unlock(tmp->right_fork_mutex);
}

void	sleeping_state(t_philo *tmp)
{
	tmp->state = SLEEPING;
	display_log(tmp->params, tmp, SLEEP);
	ft_wait_timer_ms(tmp->params->ms_to_sleep);
}

void	thinking_state(t_philo *tmp)
{
	tmp->state = THINKING;
	display_log(tmp->params, tmp, THINK);
}

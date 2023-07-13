/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:20:18 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 20:26:05 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_rested_philo(t_philo *tmp)
{
	if (tmp->params->check_eat && \
	(tmp->nb_eat >= tmp->params->nb_times_each_eat))
	{
		tmp->finish_eating = 1;
		return (1);
	}
	return (0);
}

void	eating_state(t_philo *tmp)
{
	tmp->state = EATING;
	sem_wait(tmp->params->sem_forks);
	display_log(tmp->params, tmp, LFORK);
	sem_wait(tmp->params->sem_forks);
	display_log(tmp->params, tmp, RFORK);
	tmp->start_time = ft_get_time();
	sem_wait(tmp->params->sem_eat_die);
	display_log(tmp->params, tmp, EAT);
	ft_wait_timer_ms(tmp->params->ms_to_eat);
	tmp->nb_eat++;
	sem_post(tmp->params->sem_eat_die);
	sem_post(tmp->params->sem_forks);
	sem_post(tmp->params->sem_forks);
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

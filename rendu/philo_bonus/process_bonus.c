/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:44 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 19:12:47 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_threads(t_philo *philo)
{
	if (pthread_create(&(philo->death), NULL, \
	(void *)&death_thread, (void *)philo))
		return (1);
	pthread_detach(philo->death);
	return (0);
}

void	*death_thread(void *arg)
{
	t_philo		*tmp;
	long long	elapsed;

	tmp = (t_philo *)arg;
	while (1)
	{
		if (tmp->start_time)
		{
			elapsed = elapsed_ms(tmp->start_time, ft_get_time());
			if (elapsed > tmp->params->ms_to_die)
			{
				tmp->elapsed_time = elapsed;
				sem_wait(tmp->params->sem_eat_die);
				display_log(tmp->params, tmp, DIED);
				sem_post(tmp->params->sem_eat_die);
				sem_eat_die_name(tmp, DESTROY);
				exit (1);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void	philo_process(t_philo *tmp)
{
	if (!tmp->start_time)
		tmp->start_time = ft_get_time();
	while (!tmp->died && tmp->params->valid && !tmp->finish_eating)
	{
		if (check_rested_philo(tmp))
			break ;
		if (tmp->state == THINKING)
			eating_state(tmp);
		else if (tmp->state == EATING)
			sleeping_state(tmp);
		else if (tmp->state == SLEEPING)
			thinking_state(tmp);
	}
}

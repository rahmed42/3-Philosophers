/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:44 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/31 14:16:10 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_params *params, t_philo *start, t_philo *tmp_philo, int id)
{
	while (id <= params->nb_of_philo)
	{
		tmp_philo->id = id;
		tmp_philo->state = THINKING;
		tmp_philo->params = params;
		if (pthread_mutex_init(&tmp_philo->left_fork_mutex, NULL) || \
		pthread_mutex_init(&tmp_philo->eat_die_mutex, NULL) || \
		pthread_mutex_init(&params->print_mutex, NULL) || \
		pthread_mutex_init(&params->global_mutex, NULL))
			return (1);
		if (id++ < params->nb_of_philo)
		{
			tmp_philo->next = (t_philo *)malloc(sizeof(t_philo));
			if (!tmp_philo->next)
				return (1);
			memset(tmp_philo->next, 0, sizeof(t_philo));
			tmp_philo = tmp_philo->next;
		}
		else
		{
			tmp_philo->next = start;
			tmp_philo = start;
		}
	}
	return (0);
}

int	create_threads(t_params *params, t_philo *philo)
{
	t_philo		*tmp_philo;
	int			i;

	i = 0;
	tmp_philo = philo;
	if (starting_threads(params, tmp_philo, i))
		return (1);
	usleep(2000);
	i = 1;
	tmp_philo = philo->next;
	if (starting_threads(params, tmp_philo, i))
		return (1);
	return (0);
}

int	starting_threads(t_params *params, t_philo *tmp_philo, int i)
{
	while (i < params->nb_of_philo)
	{
		if (pthread_create(&(tmp_philo->thread), NULL, \
		(void *)&philo_thread, (void *)tmp_philo))
			return (1);
		pthread_detach(tmp_philo->thread);
		usleep(100);
		if (pthread_create(&(tmp_philo->death), NULL, \
		(void *)&death_thread, (void *)tmp_philo))
			return (1);
		pthread_detach(tmp_philo->death);
		i += 2;
		usleep(100);
		tmp_philo = tmp_philo->next->next;
	}
	return (0);
}

void	*death_thread(void *arg)
{
	t_philo		*tmp;
	long long	elapsed;

	tmp = (t_philo *)arg;
	while (1)
	{
		if ((tmp->params->nb_philo_unrested == 0) || tmp->finish_eating)
			return (NULL);
		if (tmp->start_time)
		{
			elapsed = elapsed_ms(tmp->start_time, ft_get_time());
			if (elapsed > tmp->params->ms_to_die)
			{
				tmp->elapsed_time = elapsed;
				pthread_mutex_lock(&tmp->eat_die_mutex);
				display_log(tmp->params, tmp, DIED);
				pthread_mutex_unlock(&tmp->eat_die_mutex);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void	*philo_thread(void *arg)
{
	t_philo		*tmp;

	tmp = (t_philo *)arg;
	if (!tmp->params->top_time)
		tmp->params->top_time = ft_get_time();
	if (!tmp->start_time)
		tmp->start_time = ft_get_time();
	if (tmp->id % 2 == 0)
		usleep(tmp->params->ms_to_eat / 2);
	while (!tmp->died && tmp->params->valid && !tmp->finish_eating)
	{
		if (check_rested_philo(tmp))
			return (NULL);
		if (tmp->state == THINKING)
			eating_state(tmp);
		else if (tmp->state == EATING)
			sleeping_state(tmp);
		else if (tmp->state == SLEEPING)
			thinking_state(tmp);
	}
	return (NULL);
}

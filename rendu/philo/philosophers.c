/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:05:22 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 21:26:34 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	memset(params, 0, sizeof(t_params));
	philo = (t_philo *)malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	philo->params = params;
	if (philo && params && set_args(argc, argv, params))
		lunch_philo(params, philo);
	free_mutexes(philo, params);
	return (0);
}

void	lunch_philo(t_params *params, t_philo *philo)
{
	params->nb_philo_unrested = params->nb_of_philo;
	if (create_linked_philos(params, philo))
		return ;
	if (create_threads(params, philo))
		return ;
	while (1)
		if (!params->valid || !params->nb_philo_unrested)
			break ;
	if (params->nb_philo_unrested == 0)
		printf("\033[1;33m~~~ All philosophers rested ~~~\n\033[0m");
}

int	create_linked_philos(t_params *params, t_philo *philo)
{
	int			id;
	t_philo		*tmp_philo;

	tmp_philo = philo;
	id = 1;
	if (init_philo(params, philo, tmp_philo, id))
		return (1);
	tmp_philo = philo;
	while (id <= params->nb_of_philo)
	{
		tmp_philo->right_fork_mutex = &tmp_philo->next->left_fork_mutex;
		tmp_philo = tmp_philo->next;
		++id;
	}
	return (0);
}

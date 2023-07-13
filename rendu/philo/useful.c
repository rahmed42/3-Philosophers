/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:12:17 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 21:25:58 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_log(t_params *params, t_philo *philo, int err)
{
	pthread_mutex_lock(&params->print_mutex);
	if (params->valid)
	{
		if (err == DIED)
			print_message(params, philo, DIED);
		if (err == LFORK)
			print_message(params, philo, LFORK);
		if (err == RFORK)
			print_message(params, philo, RFORK);
		if (err == EAT)
			print_message(params, philo, EAT);
		if (err == SLEEP)
			print_message(params, philo, SLEEP);
		if (err == THINK)
			print_message(params, philo, THINK);
	}
	if (err == DIED)
	{
		params->valid = 0;
		philo->died = 1;
	}
	else
		pthread_mutex_unlock(&params->print_mutex);
}

void	print_message(t_params *params, t_philo *philo, int err)
{
	if (err == DIED)
	{
		printf("\033[1;31m%lld\t%d\tdied\n", \
		ft_get_time() - params->top_time, philo->id);
		printf("\033[0;41m~~~ starved %dms overflow ~~~\033[0m\n", \
		philo->elapsed_time - params->ms_to_die);
	}
	if (err == LFORK)
		printf("%lld\t%d\thas taken left fork\n", \
		ft_get_time() - params->top_time, philo->id);
	if (err == RFORK)
		printf("%lld\t%d\thas taken right fork\n", \
		ft_get_time() - params->top_time, philo->id);
	if (err == EAT)
		printf("\033[1;32m%lld\t%d\tis eating (%d)\033[0m\n", \
		philo->start_time - params->top_time, philo->id, philo->nb_eat + 1);
	if (err == SLEEP)
		printf("%lld\t%d\tis sleeping\n", \
		ft_get_time() - params->top_time, philo->id);
	if (err == THINK)
		printf("%lld\t%d\tis thinking\n", \
		ft_get_time() - params->top_time, philo->id);
	if (err == ARG)
		printf("ARG Error : ./philo <nb_of_philosophers&forks> <ms_to_die> " \
		"<ms_to_eat> <ms_to_sleep> <[nb_times_each_philosopher_must_eat]>\n");
}

int	set_args(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
	{
		print_message(params, NULL, ARG);
		return (0);
	}
	params->nb_of_philo = atoi_lite(argv[1]);
	params->ms_to_die = atoi_lite(argv[2]);
	params->ms_to_eat = atoi_lite(argv[3]);
	params->ms_to_sleep = atoi_lite(argv[4]);
	if (argv[5])
	{
		params->nb_times_each_eat = atoi_lite(argv[5]);
		params->check_eat = 1;
	}
	if ((params->nb_of_philo < 1 || params->ms_to_die <= 0 || \
	params->ms_to_eat <= 0 || params->ms_to_sleep <= 0) || \
	(argc == 6 && params->nb_times_each_eat <= 0))
	{
		print_message(params, NULL, ARG);
		return (0);
	}
	else
		params->valid = 1;
	return (1);
}

void	free_mutexes(t_philo *philo, t_params *params)
{
	t_philo	*nxt;
	int		i;

	i = 0;
	usleep(params->ms_to_sleep * 1000);
	if (philo)
	{
		while ((i < params->nb_of_philo) && philo)
		{
			pthread_mutex_destroy(&philo->left_fork_mutex);
			pthread_mutex_destroy(&philo->eat_die_mutex);
			if (i++ < params->nb_of_philo - 1)
				nxt = philo->next;
			else
				nxt = NULL;
			free(philo);
			philo = nxt;
		}
	}
	if (params)
	{
		pthread_mutex_destroy(&params->print_mutex);
		pthread_mutex_destroy(&params->global_mutex);
		free(params);
	}
}

int	atoi_lite(const char *str)
{
	size_t				i;
	unsigned long int	res;
	int					sign;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i++] - '0';
	}
	if (!((str[i] >= '0') && (str[i] <= '9')) && str[i] != '\0')
		return (0);
	return (res * sign);
}

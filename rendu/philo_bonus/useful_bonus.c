/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:12:17 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/31 14:51:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	display_log(t_params *params, t_philo *philo, int err)
{
	sem_wait(params->sem_print);
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
		sem_post(params->sem_print);
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

void	free_semaphores(t_philo *philo, t_params *params, pid_t *pid)
{
	int	i;

	i = 0;
	if (philo)
	{
		if (pid)
			while (i < params->nb_of_philo)
				kill(pid[i++], SIGKILL);
		free(philo);
	}
	sem_unlink("/print");
	sem_unlink("/fork");
	if (params)
	{
		sem_close(params->sem_print);
		sem_close(params->sem_forks);
		free(params);
	}
	if (pid)
		free(pid);
}

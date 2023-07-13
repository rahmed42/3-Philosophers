/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:05:22 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/31 14:56:32 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	*params;
	pid_t		*pid;

	params = (t_params *)malloc(sizeof(t_params));
	memset(params, 0, sizeof(t_params));
	philo = (t_philo *)malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		pid = malloc((sizeof(pid_t) * atoi_lite(argv[1])) + 1);
		memset(philo, 0, sizeof(pid_t));
	}
	if (!params || !philo)
		return (0);
	sem_unlink("/print");
	sem_unlink("/fork");
	if (philo && params && set_args(argc, argv, params))
	{
		create_philos(params, philo);
		launch_philo(params, philo, pid);
	}
	free_semaphores(philo, params, pid);
	return (0);
}

void	create_philos(t_params *params, t_philo *philo)
{
	philo->state = THINKING;
	philo->params = params;
	params->sem_forks = sem_open("/fork", O_CREAT | O_EXCL, \
	S_IRWXU | S_IRWXG | S_IRWXO, params->nb_of_philo);
	params->sem_print = sem_open("/print", O_CREAT | O_EXCL, \
	S_IRWXU | S_IRWXG | S_IRWXO, 1);
}

void	launch_philo(t_params *params, t_philo *philo, pid_t *pid)
{
	int		i;

	i = 0;
	params->top_time = ft_get_time();
	while (i < params->nb_of_philo)
	{
		if (i == (params->nb_of_philo / 2))
			usleep(params->ms_to_eat / 2);
		philo->id++;
		pid[i] = fork();
		if (pid[i] == -1)
			return ;
		if (pid[i] == 0)
		{
			if (create_threads(philo))
				return ;
			sem_eat_die_name(philo, CREATE);
			philo_process(philo);
			sem_eat_die_name(philo, DESTROY);
			exit(0);
		}
		i++;
	}
	wait_processes(params);
}

void	wait_processes(t_params *params)
{
	int	i;
	int	status;

	i = 0;
	while (i < params->nb_of_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				break ;
			else if (WEXITSTATUS(status) == 0)
				i++;
		}
	}
	if (i == params->nb_of_philo)
		printf("\033[1;33m~~~ All philosophers rested ~~~\n\033[0m");
}

void	sem_eat_die_name(t_philo *tmp, int type)
{
	if (type == CREATE)
	{
		tmp->name = ft_strjoin_del_str2("/eat_die_", ft_itoa_lite(tmp->id));
		sem_unlink(tmp->name);
		tmp->params->sem_eat_die = sem_open(tmp->name, O_CREAT | O_EXCL, \
		S_IRWXU | S_IRWXG | S_IRWXO, 1);
	}
	if (type == DESTROY)
	{
		sem_unlink(tmp->name);
		sem_close(tmp->params->sem_eat_die);
		free(tmp->name);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:24:29 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/23 19:14:32 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long long	ft_get_time(void)
{
	struct timeval	tp;
	long long		ms;

	gettimeofday(&tp, NULL);
	ms = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (ms);
}

long long	elapsed_ms(long long start, long long end)
{
	return (end - start);
}

int	ft_wait_timer_ms(long timerms)
{
	int			ms;
	long long	start;

	ms = 0;
	start = ft_get_time();
	while (ms < timerms)
	{
		usleep(500);
		ms = elapsed_ms(start, ft_get_time());
	}
	return (ms);
}

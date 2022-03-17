/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:07:02 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 02:23:45 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_philo(t_input *input, t_philo **philos)
{
	int		i;
	long	death_time;

	i = 0;
	while (philos[i] != NULL)
	{
		pthread_mutex_lock(&(input->time_lock));
		if (get_time() - philos[i]->time >= input->time_to_die)
		{
			pthread_mutex_unlock(&(input->time_lock));
			pthread_mutex_lock(&(input->death_lock));
			input->death = true;
			pthread_mutex_unlock(&(input->death_lock));
			death_time = get_time() - input->start_time;
			printf(RED"[%ld] %d is dead\n"RESET, death_time, philos[i]->philo_n);
			return (false);
		}
		pthread_mutex_unlock(&(input->time_lock));
		i++;
	}
	return (true);
}

void	ft_reaper(t_input *input, t_philo **philos)
{
	input->start_time = get_time();
	input->wait = false;
	ft_sleep(input->time_to_die / 2);
	while (true)
	{
		if (check_philo(input, philos) == false)
			break;
	}
}
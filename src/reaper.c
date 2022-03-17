/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:07:02 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 14:02:40 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	finished_eating(t_input *input, t_philo **philos)
{
	int	i;
	int	philos_done;

	i = 0;
	philos_done = 0;
	while (philos[i] != NULL)
	{
		if (philos[i]->running == false)
			philos_done++;
		i++;
	}
	if (philos_done == input->philo_count)
		return (true);
	return (false);
}

static bool	check_philo(t_input *input, t_philo **philos)
{
	int		i;
	long	death_time;

	i = 0;
	while (philos[i] != NULL)
	{
		if (input->eat_n_times != -1)
		{
			pthread_mutex_lock(&(input->eat_lock));
			if (philos[i]->eat_n_times >= input->eat_n_times)
				philos[i]->running = false;
			pthread_mutex_unlock(&(input->eat_lock));
		}
		pthread_mutex_lock(&(input->time_lock));
		if (get_time() - philos[i]->time >= input->time_to_die && philos[i]->running == true)
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
		if (finished_eating(input, philos) == true)
		{
			pthread_mutex_lock(&(input->death_lock));
			input->death = true;
			pthread_mutex_unlock(&(input->death_lock));
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_reaper(t_input *input, t_philo **philos)
{
	input->start_time = get_time();
	input->wait = false;
	ft_sleep(input->time_to_die - (input->time_to_die / 4));
	while (true)
	{
		if (check_philo(input, philos) == false)
			break;
	}
}
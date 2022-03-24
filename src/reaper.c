/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzeck <tzeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:07:02 by tom               #+#    #+#             */
/*   Updated: 2022/03/19 20:21:31 by tzeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  sets death bool and prints message
 * @param  *input: input struct
 * @param  *philo: philo struct
 * @param  dead: true if died, false if n_time_eat reached
 */
static void	death_routine(t_input *input, t_philo *philo, bool dead)
{
	long	death_time;

	pthread_mutex_lock(input->death_lock);
	input->death = true;
	pthread_mutex_unlock(input->death_lock);
	if (dead == true)
	{
		death_time = get_time() - input->start_time;
		ft_sleep(2);
		printf(RED"[%ld] %d is dead\n"RESET, death_time, philo->philo_n);
	}
}

/**
 * @brief  checks if philo ate enough
 * @param  *input: input struct
 * @param  *philo: philo struct
 */
static void	check_eat_status(t_input *input, t_philo *philo)
{
	pthread_mutex_lock(input->eat_lock);
	if (philo->eat_n_times >= input->eat_n_times)
		philo->running = false;
	pthread_mutex_unlock(input->eat_lock);
}

/**
 * @brief  checks if all philos are done eating
 * @param  *input: input struct
 * @param  **philos: philo struct
 * @retval true if done
 */
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

/**
 * @brief  checks if philo reached death time
 * @param  *input: input struct
 * @param  **philos: philo struct
 * @retval true if dead
 */
static bool	check_philo(t_input *input, t_philo **philos)
{
	int		i;

	i = 0;
	while (philos[i] != NULL)
	{
		if (input->eat_n_times != -1)
			check_eat_status(input, philos[i]);
		pthread_mutex_lock(input->time_lock);
		if (get_time() - philos[i]->time >= input->time_to_die
			&& philos[i]->running == true)
		{
			pthread_mutex_unlock(input->time_lock);
			death_routine(input, philos[i], true);
			return (false);
		}
		pthread_mutex_unlock(input->time_lock);
		if (finished_eating(input, philos) == true)
		{
			death_routine(input, philos[i], false);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief  scans philos for dead people while threads running
 * @param  *input: input struct
 * @param  **philos: philo struct
 */
void	ft_reaper(t_input *input, t_philo **philos)
{
	input->start_time = get_time();
	input->wait = false;
	ft_sleep(input->time_to_die - (input->time_to_die / 4));
	while (true)
	{
		if (check_philo(input, philos) == false)
			break ;
	}
}

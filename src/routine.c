/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:14:55 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 14:05:11 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  sleeps for time_to_sleep
 * @param  *input: input struct
 * @param  *philo: philo
 */
void	philo_sleep(t_input *input, t_philo *philo)
{
	print_state(input, philo, SLEEP);
	ft_sleep(input->time_to_sleep);
	print_state(input, philo, THINK);
}

void	philo_fork(t_input *input, t_philo *philo)
{
	// if (philo->philo_n % 2 == 0)
	// {
	pthread_mutex_lock(philo->fork_l);
	print_state(input, philo, FORK);
	if (input->philo_count == 1)
	{
		pthread_mutex_unlock(philo->fork_l);
		ft_sleep(input->time_to_die + 1);
	}
	pthread_mutex_lock(philo->fork_r);
	print_state(input, philo, FORK);
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->fork_r);
	// 	print_state(input, philo, FORK);
	// 	pthread_mutex_lock(philo->fork_l);
	// 	print_state(input, philo, FORK);
	// }
}

/**
 * @brief  claim forks, eat for time_to_eat and unlock forks
 * @note   splitted left-first / right-first to prevent deadlock
 * @param  *input: input struct
 * @param  *philo: philo
 */
void	philo_eat(t_input *input, t_philo *philo)
{
	philo_fork(input, philo);
	pthread_mutex_lock(&(input->time_lock));
	philo->time = get_time();
	pthread_mutex_unlock(&(input->time_lock));
	pthread_mutex_lock(&(input->eat_lock));
	philo->eat_n_times++;
	pthread_mutex_unlock(&(input->eat_lock));
	print_state(input, philo, EAT);
	ft_sleep(input->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

/**
 * @brief  start of routine, calls actions until dead or eat_n_times
 * @param  *input: input struct
 * @param  *philo: philo
 */
void	start_do_something(t_input *input, t_philo *philo)
{
	if (philo->philo_n % 2 == 0)
		philo_sleep(input, philo);
	while (true)
	{
		philo_eat(input, philo);
		philo_sleep(input, philo);
		pthread_mutex_lock(&(input->death_lock));
		if (input->death == true)
		{
			pthread_mutex_unlock(&(input->death_lock));
			return ;
		}
		pthread_mutex_unlock(&(input->death_lock));
	}
}

/**
 * @brief  function executed by threads (philos)
 * @param  *arg: philo and input
 */
void	*routine(void *arg)
{
	t_data			*data;
	t_input			*input;
	t_philo			*philo;

	data = (t_data *)arg;
	input = data->input;
	philo = data->philo;
	while (input->wait == true)
		continue ;
	philo->running = true;
	free(data);
	pthread_mutex_lock(&(input->time_lock));
	philo->time = input->start_time;
	pthread_mutex_unlock(&(input->time_lock));
	start_do_something(input, philo);
	return (NULL);
}

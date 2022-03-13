/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:14:55 by tom               #+#    #+#             */
/*   Updated: 2022/03/09 23:47:29 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_input *input, t_philo *philo)
{
	struct timeval	*time;
	time = malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	printf("%d %d is sleeping\n", time->tv_usec, philo->philo_n);
	usleep(input->time_to_sleep);
	gettimeofday(time, NULL);
	printf("%d %d is thinking\n", time->tv_usec, philo->philo_n);
}

void	philo_eat(t_input *input, t_philo *philo)
{
	struct timeval	*time;
	time = malloc(sizeof(struct timeval));
	pthread_mutex_lock(&(philo->fork_r));
	gettimeofday(time, NULL);
	printf("%d %d has taken a fork\n", time->tv_usec, philo->philo_n);
	pthread_mutex_lock(&(philo->fork_l));
	gettimeofday(time, NULL);
	printf("%d %d has taken a fork\n", time->tv_usec, philo->philo_n);
	usleep(input->time_to_eat);
	gettimeofday(time, NULL);
	printf("%d %d is eating\n", time->tv_usec, philo->philo_n);
	pthread_mutex_unlock(&(philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
}

void	start_do_something(t_input *input, t_philo *philo)
{
	if (philo->philo_n % 2 == 0)
	{
		// philo_eat(input, philo);
		philo_sleep(input, philo);
	}
	else
	{
		philo_sleep(input, philo);
		// philo_eat(input, philo);
	}
	while (true)
	{
		// philo_eat(input, philo);
		philo_sleep(input, philo);
	}
	PRINT_HERE();
}

/**
 * @brief  function executed by threads (philos)
 * @param  *arg: philo
 */
void	*routine(void *arg)
{
	t_data			*data;
	t_input			*input;
	t_philo			*philo;

	data = (t_data *)arg;
	input = data->input;
	philo = data->philo;
	if (philo->wait == false)
		pthread_mutex_lock(&(data->start));
	else
	{
		pthread_mutex_unlock(&(data->start));
		pthread_mutex_destroy(&(data->start));
		free(data);
	}
	start_do_something(input, philo);
	// printf("hello from philo %d\n", philo->philo_n);
	return (NULL);
}
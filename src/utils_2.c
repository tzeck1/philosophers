/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:23:52 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 17:23:32 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  free allocated space used for philos
 * @param  **philos: philo array
 */
void	free_philos(t_philo	**philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

/**
 * @brief  free all structs and destroy forks (mutex_destroy)
 * @param  **philos: philos struct
 * @param  *input: input struct
 */
void	free_all(t_philo **philos, t_input *input)
{
	destroy_forks(philos);
	pthread_mutex_destroy(input->print_lock);
	free(input->print_lock);
	pthread_mutex_destroy(input->death_lock);
	free(input->death_lock);
	pthread_mutex_destroy(input->time_lock);
	free(input->time_lock);
	pthread_mutex_destroy(input->eat_lock);
	free(input->eat_lock);
	free_philos(philos);
	free(input);
}

/**
 * @brief  calculates time passed since program execution
 * @retval time passed in milliseconds
 */
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief  prints current state of philo at start of action
 * @param  *input: input struct
 * @param  *philo: philo
 * @param  status: status code (FORK, EAT, SLEEP, THINK, DEAD)
 */
void	print_state(t_input *input, t_philo *philo, int status)
{
	long			cur_t;
	long			new_t;

	pthread_mutex_lock(input->print_lock);
	new_t = get_time();
	cur_t = new_t - input->start_time;
	if (input->death == false)
	{
		if (status == FORK)
			printf("[%ld] %d has taken a fork\n", cur_t, philo->philo_n);
		else if (status == EAT)
			printf(GREEN"[%ld] %d is eating\n"RESET, cur_t, philo->philo_n);
		else if (status == SLEEP)
			printf("[%ld] %d is sleeping\n", cur_t, philo->philo_n);
		else if (status == THINK)
			printf("[%ld] %d is thinking\n", cur_t, philo->philo_n);
	}
	pthread_mutex_unlock(input->print_lock);
}

void	ft_sleep(long time_ms)
{
	long	start_time;

	start_time = get_time();
	while (start_time + time_ms > get_time())
		usleep(100);
}

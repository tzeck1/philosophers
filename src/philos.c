/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:51:08 by tom               #+#    #+#             */
/*   Updated: 2022/03/05 20:41:47 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	pthread_mutex_t	start_wait;
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->wait == false)
		pthread_mutex_lock(&start_wait);
	else
	{
		pthread_mutex_unlock(&start_wait);
		pthread_mutex_destroy(&start_wait);
	}
	printf("hello from philo %d\n", philo->philo_n);
	return (NULL);
}

/**
 * @brief  creates thread and saves id in philo->thread_id
 * @param  **philos: philo array
 * @param  i: philo index
 * @retval error if creation fails or success
 */
static int	init_thread(t_philo **philos, int i)
{
	int	error;

	error = pthread_create(&philos[i]->thread_id, NULL, &routine, philos[i]);
	usleep(50);
	if (error != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief  creates n philo and saves in array; set number and thread_id
 * @param  *input: input struct
 * @param  **philos: philo array
 */
int	init_philos(t_input *input, t_philo **philos)
{
	int		i;

	i = 0;
	while (i < input->philo_count)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (EXIT_FAILURE);
		philos[i]->philo_n = i + 1;
				philos[i]->wait = false;
		if (i + 1 >= input->philo_count)
			philos[i]->wait = true;
		if (init_thread(philos, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	philos[i] = NULL;
	return (EXIT_SUCCESS);
}

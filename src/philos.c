/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:51:08 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 17:34:30 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_forks_l(t_philo **philos)
{
	int	i;

	i = 1;
	while (philos[i] != NULL)
	{
		philos[i]->fork_l = philos[i - 1]->fork_r;
		i++;
	}
	philos[0]->fork_l = philos[i - 1]->fork_r;
}

/**
 * @brief  init_mutex for every philos fork; give them access to left one
 * @param  **philos: philo array
 * @retval error if mutex_init for fork fails or success
 */
static int	init_forks_r(t_philo *philo)
{
	int	error;

	philo->fork_r = ft_calloc(1, sizeof(pthread_mutex_t));
	error = pthread_mutex_init(philo->fork_r, NULL);
	if (error != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief  creates thread and saves id in philo->thread_id
 * @param  **philos: philo array
 * @param  i: philo index
 * @retval error if creation fails or success
 */
static int	init_threads(t_input *input, t_philo **philos, int i)
{
	int		error;
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (EXIT_FAILURE);
	data->input = input;
	data->philo = philos[i];
	error = pthread_create(&philos[i]->thread_id, NULL, &routine, data);
	usleep(100);
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
	int	i;

	i = 0;
	while (i < input->philo_count)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (EXIT_FAILURE);
		philos[i]->philo_n = i + 1;
		philos[i]->eat_n_times = 0;
		if (init_forks_r(philos[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	philos[i] = NULL;
	init_forks_l(philos);
	i = 0;
	while (philos[i] != NULL)
	{
		if (init_threads(input, philos, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:51:08 by tom               #+#    #+#             */
/*   Updated: 2022/03/14 22:33:26 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  created locked left fork if only one philo is simulated
 * @note	maybe find better way, kinda scuffed implementation to cut lines
 * @param  **philos: philo struct
 */
void	one_philo(t_philo **philos)
{
	pthread_mutex_init(&(philos[0]->fork_l), NULL);
	pthread_mutex_lock(&(philos[0]->fork_l));
}

/**
 * @brief  init_mutex for every philos fork; give them access to left one
 * @param  **philos: philo array
 * @retval error if mutex_init for fork fails or success
 */
static int	init_forks(t_input *input, t_philo **philos)
{
	int	i;
	int	error;

	i = 0;
	while (philos[i] != NULL)
	{
		error = pthread_mutex_init(&philos[i]->fork_r, NULL);
		if (error != 0)
		{
			destroy_forks(philos);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 1;
	while (philos[i] != NULL)
	{
		philos[i]->fork_l = philos[i - 1]->fork_r;
		i++;
	}
	philos[0]->fork_l = philos[i - 1]->fork_r;
	if (input->philo_count == 1)
		one_philo(philos);
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
	pthread_mutex_init(&(data->start), NULL);
	error = pthread_create(&philos[i]->thread_id, NULL, &routine, data);
	usleep(50);
	// free(data);
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
		philos[i]->dead = false;
		philos[i]->wait = true;
		if (i + 1 >= input->philo_count)
			philos[i]->wait = false;
		if (init_forks(input, philos) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (init_threads(input, philos, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	philos[i] = NULL;
	return (EXIT_SUCCESS);
}

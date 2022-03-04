/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:51:08 by tom               #+#    #+#             */
/*   Updated: 2022/03/04 19:19:46 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine()
{
	return (NULL);
}

/**
 * @brief  creates thread and saves id in philo->thread_id
 * @param  **philos: philo array
 * @param  i: philo index
 * @retval error or success
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
		if (init_thread(philos, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	philos[i] = NULL;
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/03/17 19:38:27 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  prints expected input for user after input error
 */
void	ft_print_help(void)
{
	printf(YELLOW "./philo\t"RESET);
	printf(YELLOW"[n of philos] "RESET);
	printf(YELLOW"[time to die] "RESET);
	printf(YELLOW"[time to eat] "RESET);
	printf(YELLOW"[time to sleep] "RESET);
	printf(YELLOW"[n times philo must eat]\n" RESET);
}

/**
 * @brief  calls thread_join; frees philos and input after
 * @param  *input: input struct
 * @param  **philos: philo array
 * @retval error if join fails or success
 */
static int	ft_terminate(t_input *input, t_philo **philos)
{
	int	i;
	int	error;

	i = 0;
	while (philos[i] != NULL)
	{
		error = pthread_detach(philos[i]->thread_id);
		if (error != 0)
		{
			ft_print_error(RED"Error while waiting for threads!"RESET);
			free_all(philos, input);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free_all(philos, input);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;

	if (argc < 5 || argc > 6)
	{
		ft_print_error(RED"Wrong number of arguments!"RESET);
		ft_print_help();
		return (EXIT_FAILURE);
	}
	input = init_input(argv);
	if (input == NULL)
		return (EXIT_FAILURE);
	philos = malloc((input->philo_count + 1) * sizeof(t_philo));
	if (init_philos(input, philos) == EXIT_FAILURE)
	{
		ft_print_error(RED"Error while creating philos!\n"RESET);
		return (EXIT_FAILURE);
	}
	ft_reaper(input, philos);
	ft_terminate(input, philos);
	return (EXIT_SUCCESS);
}

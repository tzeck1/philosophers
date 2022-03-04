/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/03/04 19:28:28 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  prints expected input for user after input error
 */
void	ft_print_help(void)
{
	printf(YELLOW "./philo\t"RESET);
	printf(YELLOW"[n of philos]  "RESET);
	printf(YELLOW"[time to die]  "RESET);
	printf(YELLOW"[time to eat]  "RESET);
	printf(YELLOW"[time to sleep]  "RESET);
	printf(YELLOW"[n times philo must eat]\n" RESET);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;

	if (argc < 5 || argc > 6)
	{
		ft_print_error(RED"Wrong number of arguments!\n"RESET);
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
	free_philos(philos);
	free(input);
	system("leaks philo");
	return (EXIT_SUCCESS);
}

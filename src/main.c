/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/03/06 14:58:04 by tom              ###   ########.fr       */
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
		error = pthread_join(philos[i]->thread_id, NULL);
		if (error != 0)
		{
			ft_print_error(RED"Error while waiting for threads!"RESET);
			destroy_forks(philos);
			free_philos(philos);
			free(input);
			return (EXIT_FAILURE);
		}
		i++;
	}
	destroy_forks(philos);
	free_philos(philos);
	free(input);
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
	/*	testing	*/
	// int i = 0;
	// while (philos[i] != NULL)
	// {
	// 	printf("philo %d: \n", philos[i]->philo_n);
	// 	write(1, "right: ", 8);
	// 	write(1, &philos[i]->fork_r, sizeof(pthread_mutex_t));
	// 	write(1, "\n", 1);
	// 	write(1, "left: ", 7);
	// 	write(1, &philos[i]->fork_l, sizeof(pthread_mutex_t));
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	/*	testing	*/
	ft_terminate(input, philos);
	// system("leaks philo");
	return (EXIT_SUCCESS);
}

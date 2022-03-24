/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzeck <tzeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:38:46 by tom               #+#    #+#             */
/*   Updated: 2022/03/19 20:24:07 by tzeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  tests for empty string like <4 "" 100 100>
 * @param  argc: n of arguments
 * @param  **argv: arguments
 * @retval false for empty argument
 */
static bool	check_empty(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
		{
			ft_print_error(RED"Input can't be empty!"RESET);
			ft_print_help();
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief  alloc all mutex and init them
 * @param  *input: input struct
 * @retval error code
 */
static int	init_mutex(t_input *input)
{
	int	error;

	input->print_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	input->death_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	input->time_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	input->eat_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (input->print_lock == NULL || input->death_lock == NULL
		|| input->time_lock == NULL || input->eat_lock == NULL)
		return (-1);
	error = pthread_mutex_init(input->print_lock, NULL);
	error += pthread_mutex_init(input->death_lock, NULL);
	error += pthread_mutex_init(input->time_lock, NULL);
	error += pthread_mutex_init(input->eat_lock, NULL);
	return (error);
}

/**
 * @brief  returns true if input is only numeric, false if not
 */
static bool	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if ((ft_isdigit(argv[i][j]) == false) ||
				(ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 0))
			{
				ft_print_error(RED"Wrong Input Type!"RESET);
				ft_print_help();
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief  saves user input in struct
 * @param  *input: input struct
 * @param  **argv: user input
 * @retval input struct
 */
static t_input	*save_input(t_input *input, char **argv)
{
	int	error;

	input->philo_count = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		input->eat_n_times = ft_atoi(argv[5]);
	else
		input->eat_n_times = -1;
	input->death = false;
	input->wait = true;
	error = init_mutex(input);
	if (error != 0)
		return (NULL);
	return (input);
}

/**
 * @brief  checks input and creates input struct
 * @param  **argv: user input
 * @retval input struct
 */
t_input	*init_input(int argc, char **argv)
{
	t_input	*input;

	if (check_empty(argc, argv) == false)
		return (NULL);
	if (check_input(argv) == false)
		return (NULL);
	if (ft_atoi(argv[1]) == 0)
	{
		ft_print_error(RED"Simulation needs at least one philo!"RESET);
		ft_print_help();
		return (NULL);
	}
	input = ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL);
	input = save_input(input, argv);
	return (input);
}

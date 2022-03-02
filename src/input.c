/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:38:46 by tom               #+#    #+#             */
/*   Updated: 2022/03/02 00:56:31 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
			if (ft_isdigit(argv[i][j]) == false)
			{
				printf(RED "Wrong Input Type!\n" RESETCOLOR);
				ft_print_help();
				return (false);
			}
			if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) <= 0)
				return (false);
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
	input->philo_count = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		input->eat_n_times = ft_atoi(argv[5]);
	else
		input->eat_n_times = -1;
	return (input);
}

/**
 * @brief  checks input and creates input struct
 * @param  **argv: user input
 * @retval input struct
 */
t_input	*init_input(char **argv)
{
	t_input	*input;

	if (check_input(argv) == false)
		return (NULL);
	input = ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL);
	input = save_input(input, argv);
	return (input);
}

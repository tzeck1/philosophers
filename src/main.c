/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/03/01 23:56:56 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  prints expected input for user after input error
 */
void	ft_print_help(void)
{
	printf(YELLOW"./philo\t"RESETCOLOR);
	printf(YELLOW"[n of philos]  "RESETCOLOR);
	printf(YELLOW"[time to die]  "RESETCOLOR);
	printf(YELLOW"[time to eat]  "RESETCOLOR);
	printf(YELLOW"[time to sleep]  "RESETCOLOR);
	printf(YELLOW"[n times philo must eat]\n"RESETCOLOR);
}

int	main(int argc, char **argv)
{
	t_input	*input;

	if (argc < 5 || argc > 6)
	{
		printf(RED"Wrong number of arguments!\n"RESETCOLOR);
		ft_print_help();
		return (1);
	}
	input = init_input(argv);
	if (input == NULL)
		return (1);
	return (0);
}

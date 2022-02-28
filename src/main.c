/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/02/28 19:38:11 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_help(void)
{
	printf(BLUE"./philo\t"RESETCOLOR);
	printf(BLUE"[n of philos]  "RESETCOLOR);
	printf(BLUE"[time to die]  "RESETCOLOR);
	printf(BLUE"[time to eat]  "RESETCOLOR);
	printf(BLUE"[time to sleep]  "RESETCOLOR);
	printf(BLUE"[n times philo must eat]\n"RESETCOLOR);
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

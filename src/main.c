/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/02/28 19:23:40 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_help(void)
{
	printf("./philo\t");
	printf(GREEN"[n of philos]  "RESETCOLOR);
	printf(BLUE"[time to die]  "RESETCOLOR);
	printf(PURPLE"[time to eat]  "RESETCOLOR);
	printf(RED"[time to sleep]  "RESETCOLOR);
	printf(YELLOW"[n times philo must eat]\n"RESETCOLOR);
}

int	main(int argc, char **argv)
{
	t_input	*input;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!\n");
		ft_print_help();
		return (1);
	}
	input = init_input(argv);
	if (input == NULL)
		return (1);
	return (0);
}

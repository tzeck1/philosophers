/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:31 by tom               #+#    #+#             */
/*   Updated: 2022/02/18 16:29:00 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments");
		return (1);
	}
	input = init_input(argv);
	if (input == NULL)
		return (1);
	return (0);
}
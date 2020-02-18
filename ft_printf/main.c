/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:53:00 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/29 11:21:37 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(void)
{
	char	*str;
	char	**p;
	char	*tmp;
	int		i;
	int		k;

	str = "qwezxcs";
	tmp = "asd";
	p = &tmp;
	i = ft_printf("%f", 1.501);
	write(1, "\n", 1);
	k = printf("%f", 1.501);
	if (k == i)
		printf("\nReturned Value Sucesess");
	return (0);
}

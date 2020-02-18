/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:55:17 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:25:30 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_width_c(t_printf *data)
{
	while (data->width > data->len)
	{
		write(1, " ", 1);
		data->width--;
		data->result++;
	}
}

void	do_minus_c2(t_printf *data, char c)
{
	ft_putchar(c);
	do_width_c(data);
}

void	do_no_minus_c2(t_printf *data, char c)
{
	if (data->width > data->len)
		do_width_c(data);
	ft_putchar(c);
}

void	do_c(va_list list, t_printf *data)
{
	int		type;
	char	c;

	type = (unsigned char)va_arg(list, int);
	c = type;
	data->len = 1;
	data->result += 1;
	if (data->minus == 1)
		do_minus_c2(data, c);
	else
		do_no_minus_c2(data, c);
}

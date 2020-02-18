/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 08:51:26 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/29 09:05:41 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_f_len(long double type)
{
	int i;

	i = 0;
	while (type > 1)
	{
		type /= 10;
		i++;
	}
	return (i);
}

void	do_width_f(t_printf *data)
{
	while (data->len < data->width)
	{
		if (data->zero == 1 && data->minus == 0)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		data->width--;
		data->result++;
	}
}

void	do_no_minus_f(t_printf *data, long double type)
{
	do_width_f(data);
	if (data->plus == 1)
	{
		write(1, "+", 1);
		data->result++;
	}
	ft_putnbr_f(type, data);
}

void	do_minus_f(t_printf *data, long double type)
{
	if (data->plus == 1)
	{
		write(1, "+", 1);
		data->result++;
	}
	ft_putnbr_f(type, data);
	do_width_f(data);
}

void	init_f(t_printf *data)
{
	if (data->precision == -1)
		data->precision = 0;
	if (data->precision == 0)
		data->precision = 6;
	if (data->plus == 1)
		data->width--;
}

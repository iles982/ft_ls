/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 23:33:09 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/25 23:33:18 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_width(t_printf *data)
{
	check_it(data);
	if (data->len > data->precision)
	{
		while (data->width > data->len)
		{
			if (data->zero == 1 && !data->precision && data->minus != 1)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			data->width--;
			data->result++;
		}
	}
	else if (data->precision > data->len)
	{
		while (data->width > data->precision)
		{
			if (data->zero == 1 && !data->precision && data->minus != 1)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			data->width--;
			data->result++;
		}
	}
}

void	do_precision(t_printf *data)
{
	int i;

	i = ft_strlen(data->data);
	if (data->precision > data->len)
		data->len += data->precision - data->len;
	while (data->precision > i)
	{
		write(1, "0", 1);
		data->precision--;
		data->result++;
	}
}

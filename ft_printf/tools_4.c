/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:17:59 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/25 23:29:30 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_it(t_printf *data)
{
	if (data->plus == 1 && data->type >= 0)
		data->width--;
}

void	ft_putnbr_u(unsigned long long n)
{
	if (n >= 10)
		ft_putnbr_u(n / 10);
	ft_putchar((n % 10) + '0');
}

void	check_2(t_printf *data, long long type)
{
	if (data->plus == 1 && type >= 0)
		data->width--;
}

void	int_init(t_printf *data, long long type)
{
	if (type == -9223372036854775806 - 2)
	{
		data->data = ft_strnew(21);
		data->data = ft_strcpy(data->data, "-9223372036854775808");
	}
	else
		data->data = ft_itoa(type);
	data->len = ft_strlen(data->data);
	if (data->precision == -1)
		data->len = 0;
	data->hash = 0;
	data->difference = data->precision - data->len;
}

void	do_width_spec(t_printf *data, long long type)
{
	costil_2(data, type);
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

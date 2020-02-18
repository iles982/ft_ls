/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:39:32 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/25 22:47:39 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_minus_x(t_printf *data)
{
	if (data->hash == 1)
		ft_putstr("0x");
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	do_width(data);
	data->result += ft_strlen(data->data);
}

void	do_no_minus_x(t_printf *data)
{
	if (data->zero == 1 && data->hash == 1 && ft_atoi(data->data) != 0)
		ft_putstr("0x");
	do_width(data);
	if (data->hash == 1 && data->zero == 0 && ft_atoi(data->data) != 0)
		ft_putstr("0x");
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	data->result += ft_strlen(data->data);
}

void	init_x(t_printf *data)
{
	data->len = ft_strlen(data->data);
	data->difference = data->precision - data->len;
	if (data->hash == 1 && ft_atoi(data->data) != 0)
	{
		data->len += 2;
		data->result += 2;
	}
}

void	do_x(char *str, va_list list, t_printf *data)
{
	unsigned long long		type;

	if (spec_check(str, data->k) == 0)
		type = (unsigned int)va_arg(list, unsigned long long);
	else
	{
		if (change_type(str, data->k) == 1)
			type = (unsigned long int)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 2)
			type = (unsigned char)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 3)
			type = (unsigned short int)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 4)
			type = (unsigned long long int)va_arg(list, unsigned long long);
	}
	if (data->precision != -1)
		data->data = ft_get_x(type);
	else
		data->data = ft_strnew(1);
	init_x(data);
	if (data->minus == 1)
		do_minus_x(data);
	if (data->minus != 1)
		do_no_minus_x(data);
	free(data->data);
}

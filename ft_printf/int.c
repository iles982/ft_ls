/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:07:11 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:31:22 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	no_minus_int_2(t_printf *data, long long type)
{
	if (data->plus == 1 && type >= 0 && data->zero != 1)
	{
		write(1, "+", 1);
		data->result++;
		data->len++;
	}
	else if (data->space == 1 && data->plus != 1 &&
	type >= 0 && data->width < data->len)
	{
		write(1, " ", 1);
		data->result++;
		data->len++;
	}
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
		data->result += ft_strlen(data->data);
	}
	if (data->precision == -1 && data->width == 0 && data->type != 0)
	{
		do_width(data);
		ft_putstr(data->data);
		data->result += ft_strlen(data->data);
	}
}

void	width_precision(t_printf *data)
{
	if (data->precision > data->len)
		data->width--;
	do_width(data);
	write(1, "-", 1);
	data->result++;
	free(data->data);
	data->type *= -1;
	data->data = ft_itoa(data->type);
	do_precision(data);
	ft_putstr(data->data);
	data->result += ft_strlen(data->data);
}

void	costil(t_printf *data, long long type)
{
	write(1, "-", 1);
	data->result++;
	free(data->data);
	data->type *= -1;
	data->data = ft_itoa(data->type);
	if (type == -9223372036854775806 - 2)
	{
		data->data = ft_strnew(20);
		data->data = ft_strcpy(data->data, "9223372036854775808");
	}
}

void	do_no_minus_int(t_printf *data, long long type)
{
	if (data->zero == 1 && data->plus == 1 && data->type >= 0)
	{
		write(1, "+", 1);
		data->result++;
	}
	if (data->width > data->precision && data->type < 0 && data->precision != 0
	&& data->zero != 1)
	{
		width_precision(data);
		return ;
	}
	if ((data->type < 0 && data->len > data->width) ||
	(data->type < 0 && data->zero == 1) || (data->type < 0 &&
	data->width < data->precision))
		costil(data, type);
	do_width_spec(data, type);
	no_minus_int_2(data, type);
}

void	do_int(char *str, va_list list, t_printf *data)
{
	long long		type;

	if (spec_check(str, data->k) == 0)
		type = (int)va_arg(list, long long);
	else
	{
		if (change_type(str, data->k) == 1)
			type = (long int)va_arg(list, long long);
		else if (change_type(str, data->k) == 2)
			type = (signed char)va_arg(list, long long);
		else if (change_type(str, data->k) == 3)
			type = (short int)va_arg(list, long long);
		else
			type = (long long int)va_arg(list, long long);
	}
	data->type = type;
	int_init(data, type);
	if (data->minus == 1)
		do_minus_int(data);
	else
		do_no_minus_int(data, type);
	free(data->data);
}

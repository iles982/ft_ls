/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:20:49 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:28:48 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			do_minus_o(t_printf *data)
{
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	if (data->hash == 1 && data->precision == -1)
	{
		write(1, "0", 1);
		data->result++;
	}
	do_width(data);
	data->result += ft_strlen(data->data);
}

void			do_no_minus_o(t_printf *data)
{
	do_width(data);
	if (data->hash == 1 && data->precision == -1)
	{
		ft_putstr(data->data);
		data->result += data->len;
		return ;
	}
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	data->result += ft_strlen(data->data);
}

void			init_o(t_printf *data)
{
	if (data->hash == 1 && ft_atoi(data->data) != 0)
		data->data = ft_strjoin("0", data->data);
	data->len = ft_strlen(data->data);
	data->difference = data->precision - data->len;
}

long long		get_o(t_printf *data, char *str, va_list list)
{
	unsigned long long type;

	if (change_type(str, data->k) == 1)
		type = (unsigned long int)va_arg(list, unsigned long long);
	else if (change_type(str, data->k) == 2)
		type = (unsigned char)va_arg(list, unsigned long long);
	else if (change_type(str, data->k) == 3)
		type = (unsigned short int)va_arg(list, unsigned long long);
	else
		type = (unsigned long long)va_arg(list, unsigned long long);
	return (type);
}

void			do_o(char *str, va_list list, t_printf *data)
{
	unsigned long long		type;

	if (spec_check(str, data->k) == 0)
		type = (unsigned int)va_arg(list, unsigned long long);
	else
		type = get_o(data, str, list);
	data->type = type;
	if (data->precision != -1 || data->hash == 1)
	{
		ft_trans_to_o(type, data);
	}
	else
		data->data = ft_strnew(1);
	init_o(data);
	if (data->minus == 1)
		do_minus_o(data);
	else
		do_no_minus_o(data);
	free(data->data);
}

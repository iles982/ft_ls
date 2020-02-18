/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:53:13 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/02 14:56:24 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		list;
	t_printf	*data;

	va_start(list, format);
	if (!(data = (t_printf *)malloc(sizeof(t_printf))))
		return (-1);
	get_zero_value(data);
	data->result = start_printf((char *)format, data, list);
	va_end(list);
	free(data);
	return (data->result);
}

int		start_printf(char *str, t_printf *data, va_list list)
{
	int		result;

	result = 0;
	while (str[data->i] != '\0')
	{
		data->i = ft_find_percent(str, data->i, data);
		data->k = ft_find_type(str, data->i);
		get_new_data(data, str);
		do_type(data, str, list);
		data->i = data->k + 1;
		result += data->result;
		if (str[data->k + 1] == '\0' || str[data->k] == '\0')
			return (data->result);
	}
	return (data->result);
}

void	percent_width(t_printf *data)
{
	if (data->minus == 1)
		write(1, "%", 1);
	while (data->width >= 2)
	{
		write(1, " ", 1);
		data->result++;
		data->width--;
	}
	if (data->minus != 1)
		write(1, "%", 1);
	data->result++;
}

int		percent(t_printf *data)
{
	data->len = 0;
	percent_width(data);
	return (0);
}

void	do_type(t_printf *data, char *str, va_list list)
{
	if (str[data->k] == 'd' || str[data->k] == 'i')
		do_int(str, list, data);
	else if (str[data->k] == 'o')
		do_o(str, list, data);
	else if (str[data->k] == 'u')
		do_u(str, list, data);
	else if (str[data->k] == 'x')
		do_x(str, list, data);
	else if (str[data->k] == 'X')
		do_big_x(str, list, data);
	else if (str[data->k] == 'c')
		do_c(list, data);
	else if (str[data->k] == 's')
		do_s(list, data);
	else if (str[data->k] == 'p')
		do_p(list, data);
	else if (str[data->k] == 'f')
		do_f(str, list, data);
	else if (str[data->k] == '%')
		percent(data);
	else if (str[data->k] == '\0')
		return ;
}

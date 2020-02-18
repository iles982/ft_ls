/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:53:04 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/25 23:31:29 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_i(char *str, int i, t_printf *data)
{
	data->k = 1;
	while (str[i] != '%' && str[i])
	{
		ft_putchar(str[i]);
		i++;
		data->result++;
	}
	while (str[i] == '%' && str[i + 1] == '%' && str[i])
	{
		i++;
		data->k++;
	}
	return (i);
}

void	ft_find_percent_2(int k, t_printf *data)
{
	k = (k - 1) / 2;
	while (k > 0)
	{
		ft_putchar('%');
		data->result++;
		k--;
	}
}

void	costil_2(t_printf *data, long long type)
{
	check_2(data, type);
	if (data->space == 1 && data->zero == 1)
	{
		write(1, " ", 1);
		data->width--;
		data->result++;
	}
}

void	big_x(t_printf *data, long long type)
{
	data->data = ft_get_x(type);
	data->data = ft_big_x(data->data);
}

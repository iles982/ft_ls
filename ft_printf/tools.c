/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:15:09 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/23 03:53:14 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_find_percent(char *str, int i, t_printf *data)
{
	int k;

	i = find_i(str, i, data);
	k = data->k;
	if (k % 2 == 0)
	{
		k = k / 2;
		while (k > 0)
		{
			ft_putchar('%');
			data->result++;
			k--;
		}
		return (ft_find_percent(str, i + 1, data));
	}
	else
		ft_find_percent_2(k, data);
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}

void	get_zero_value(t_printf *data)
{
	data->hash = 0;
	data->minus = 0;
	data->plus = 0;
	data->space = 0;
	data->zero = 0;
	data->width = 0;
	data->result = 0;
	data->i = 0;
	data->data = NULL;
}

int		ft_find_type(char *str, int i)
{
	if (str[i] == '\0')
		return (i);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd'
	&& str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && str[i] != 'x' &&
	str[i] != 'X' && str[i] != 'f' && str[i] != '%')
	{
		i++;
		if (str[i] == '\0' || str[i] == '%')
			break ;
	}
	return (i);
}

int		spec_check(char *str, int k)
{
	int res;

	res = 0;
	k = k - 1;
	if (str[k] == 'l' || str[k] == 'h')
		res = 1;
	return (res);
}

void	get_new_data(t_printf *data, char *str)
{
	data->width = check_width(str, data->i, data->k);
	data->precision = check_precision(str, data->k);
	data->minus = check_minus_flags(str, data->i);
	data->plus = check_plus_flag(str, data->i);
	data->hash = check_hashtag_flag(str, data->i);
	data->zero = check_zero_flag(str, data->i);
	data->space = check_space_flag(str, data->i);
}

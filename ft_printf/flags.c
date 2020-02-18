/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:24:33 by tclarita          #+#    #+#             */
/*   Updated: 2019/11/21 18:24:45 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_hashtag_flag(char *str, int i)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
	|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == '#')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_space_flag(char *str, int i)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
	|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_zero_flag(char *str, int i)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
	|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == '0')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_plus_flag(char *str, int i)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
	|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == '+')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_minus_flags(char *str, int i)
{
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
	|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == '-')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

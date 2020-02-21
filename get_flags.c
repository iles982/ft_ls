/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:50:39 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/18 19:13:08 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(char **tmp)
{
	ft_printf("Error\n");
	exit(1);
}

void	check_flag(t_flags *flags, char *tmp)
{
	int i;

	i = 1;
	while (tmp[i])
	{
		if (tmp[i] == 'l')
			flags->l = 1;
		else if (tmp[i] == 'a')
			flags->a = 1;
		else if (tmp[i] == 'r')
			flags->r = 1;
		else if (tmp[i] == 'R')
			flags->rr = 1;
		else if (tmp[i] == 't')
			flags->t = 1;
		else if (tmp[i] == '\0')
			return ;
		else
		{
			ft_printf("ft_ls: illegal option -- %c", tmp[i]);
			exit(1);
		}
		i++;
	}
}

void	get_flags(t_flags *flags, char **str)
{
	char	**tmp;

	if (str[flags->i][0] == '-' && str[flags->i][1] == '\0')
	{
		ft_printf("%s\n", "ft_ls: -: No such file or directory");
		return ;
	}
	while (str[flags->i] && str[flags->i][0] == '-')
	{
		check_flag(flags, str[flags->i]);
		flags->i++;
	}
}

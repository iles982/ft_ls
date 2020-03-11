/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:58:50 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/11 17:46:06 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_arg(t_flags *flags, char *tmp)
{
	t_ls		*ls;
	t_data		**data;
	t_data		*start;
	char		*str;

	str = tmp;
	new_parse(flags, str);
}

int		main(int ac, char **av)
{
	t_data			*start;
	t_flags			flags[1];
	struct winsize	ws;

	init_flags(flags);
	if (ac != 1 && av[1][0] == '-')
		get_flags(flags, av);
	if (ac == flags->i)
	{
		do_arg(flags, ".");
		if (flags->l == 0)
			write(1, "\n", 1);
	}
	else
		while (ac > flags->i)
		{
			flags->p = 1;
			do_arg(flags, av[flags->i]);
			if ((flags->i < ac && (flags->i + 1 < ac && flags->l == 1)) || flags->l == 0)
			write(1, "\n", 1);
			flags->i++;
		}
}

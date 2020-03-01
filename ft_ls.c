/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:58:50 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 04:29:52 by tclarita         ###   ########.fr       */
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
		do_arg(flags, ".");
	else
		while (ac > flags->i)
		{
			do_arg(flags, av[flags->i]);
			write(1, "\n", 1);
			flags->i++;
		}
	// t_ls *ls;
	// t_data *data;
	// t_flags *flags;
	// struct dirent	*name;
	// struct stat		*stat1;
	// ls = (t_ls *)malloc(sizeof(t_ls));
	// data = (t_data *)malloc(sizeof(t_data) * 100);
	// ls->dir = opendir("./123/ft_ls.dSYM/Contents");
	// ls->i = 0;
	// while ((name = readdir(ls->dir)) > 0)
	// {
	// 	stat1 = (struct stat *)malloc(sizeof(struct stat));
	// 	lstat(name->d_name, stat1);
	// 	parse_data(&data[ls->i], stat1, flags, name);
	// 	ls->i++;
	// 	ft_printf("%s %3d %s  %s %6d %s %s\n", data[ls->i].mode, data[ls->i].link, data[ls->i].usid, data[ls->i].grid,
	// 		data[ls->i].size, data[ls->i].time, data[ls->i].name);
	// 	free(stat1);
	// }
	// return (0);
}

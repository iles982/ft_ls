/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:58:50 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/14 20:44:56 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ls		*ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->dir = opendir("./");
	while ((ls->name = readdir(ls->dir)))
	{
		printf("%s\n", ls->name->d_name);
	}
	free(ls);
	return (0);
}

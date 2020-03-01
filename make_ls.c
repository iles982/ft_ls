/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:49:55 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 05:59:58 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	make_ls_1(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	struct stat		stat1;
	struct dirent	*name;
	char			*path1;

	while ((name = readdir(ls->dir)))
		if (name->d_name[0] < 91)
			if ((name->d_name[0] == '.' && flags->a == 1) ||
			name->d_name[0] != '.')
			{
				path1 = get_path(path, name->d_name);
				stat(path1, &stat1);
				parse_data(&data[ls->i + ls->d], &stat1, flags, name);
				ls->blocks += stat1.st_blocks;
				ls->i++;
				free(path1);
			}
}

void	make_ls(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	struct stat		stat1;
	struct dirent	*name;
	char			*path1;

	if (ls->d != 0)
		write(1, "\n", 1);
	make_ls_1(data, ls, flags, path);
	closedir(ls->dir);
	ls->dir = opendir(path);
	while ((name = readdir(ls->dir)))
		if (name->d_name[0] > 90)
		{
			path1 = get_path(path, name->d_name);
			stat(path1, &stat1);
			parse_data(&data[ls->i + ls->d], &stat1, flags, name);
			ls->blocks += stat1.st_blocks;
			ls->i++;
			free(path1);
		}
	ls->d += ls->i;
	ls->b = ls->i;
	closedir(ls->dir);
}

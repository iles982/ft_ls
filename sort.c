/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:30:31 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/11 16:16:58 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_files_t(t_data *data, int max, t_ls *ls)
{
	int		i;
	int		d;
	t_data	tmp;

	max = 100;
	i = 0;
	d = ls->a;
	while (max--)
	{
		i = 0;
		while (i < ls->i)
		{
			if (data[i + d].time1 - data[i + d + 1].time1 < 0)
			{
				tmp = data[i + d];
				data[i + d] = data[i + 1];
				data[i + d + 1] = tmp;
			}
			i++;
		}
	}
}

char		*get_path_2(char *path, char *name, t_ls *ls)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, name);
	free(tmp);
	free(path);
	ls->i = 0;
	ft_printf("\n%s:", tmp2);
	return (tmp2);
}

int			open_dir(t_ls *ls)
{
	if (!(ls->dir = opendir(ls->path)))
	{
		ft_printf("ft_ls: %s: No such file or directory", ls->path);
		return (1);
	}
	return (0);
}

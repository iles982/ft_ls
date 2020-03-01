/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:02:09 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 05:00:36 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_flags(t_flags *flags)
{
	flags->i = 1;
	flags->l = 0;
	flags->a = 0;
	flags->t = 0;
	flags->r = 0;
	flags->rr = 0;
	flags->max_len_group = 0;
	flags->max_len_owner = 0;
	flags->max_len_links = 0;
	flags->max_len_size = 0;
	flags->max_len_name = 0;
}

void	check_len(t_data data, t_flags *flags)
{
	if (ft_int_len(data.link) > flags->max_len_links)
		flags->max_len_links = ft_int_len(data.link) + 1;
	if (ft_strlen(data.usid) > flags->max_len_owner)
		flags->max_len_owner = ft_strlen(data.usid) + 1;
	if (ft_strlen(data.grid) > flags->max_len_group)
		flags->max_len_group = ft_strlen(data.grid) + 1;
	if (ft_int_len(data.size) > flags->max_len_size)
		flags->max_len_links = ft_int_len(data.link) + 1;
	if (ft_strlen(data.name) > flags->max_len_name)
		flags->max_len_name = ft_strlen(data.name) + 1;
}

char	*return_path(char *path)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = 0;
	if (ft_strcmp(path, "./") == 0)
		return (path);
	while (path[i])
	{
		if (path[i] == '/')
			k = i;
		i++;
	}
	tmp = ft_strnew(k);
	tmp = ft_strncpy(tmp, path, k);
	free(path);
	return (tmp);
}

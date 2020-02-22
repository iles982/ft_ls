/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:43:17 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/21 20:35:37 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_st_mode(mode_t st_mode)
{
	char *tmp;

	tmp = ft_strnew(11);
	if (st_mode & S_IFDIR)
		tmp[0] = 'd';
	else
		tmp[0] = '-';
	tmp[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	tmp[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	tmp[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	tmp[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	tmp[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	tmp[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	tmp[7] = (st_mode & S_IROTH) ? 'r' : '-';
	tmp[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	tmp[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	tmp[10] = '\0';
	return (tmp);
}

char	*get_time(char *str)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = ft_strnew(13);
	i = 4;
	k = 0;
	while (str[i] && k < 12)
	{
		tmp[k] = str[i];
		k++;
		i++;
	}
	return (tmp);
}

char	*get_usid(uid_t st_uid)
{
	struct passwd	*uid;
	char			*tmp;

	uid = getpwuid(st_uid);
	tmp = ft_strnew(ft_strlen(uid->pw_name));
	tmp = ft_strcpy(tmp, uid->pw_name);
	return(tmp);
}

char	*get_grid(gid_t gid)
{
	struct group	*grid;
	char			*tmp;

	grid = getgrgid(gid);
	tmp = ft_strnew(ft_strlen(grid->gr_name));
	tmp = ft_strcpy(tmp, grid->gr_name);
	return(tmp);
}

void	parse_data(t_data *data, t_ls *ls, t_flags *flags)
{
	data->mode = get_st_mode(ls->stat->st_mode);
	data->link = ls->stat->st_nlink;
	data->usid = get_usid(ls->stat->st_uid);
	data->grid = get_grid(ls->stat->st_gid);
	data->size = ls->stat->st_size;
	data->time = get_time(ctime(&(ls->stat->st_mtimespec.tv_sec)));
	data->name = ft_strdup(ls->name->d_name);
	data->time_t = ls->stat->st_mtimespec.tv_sec;
	check_len(data, flags);
}

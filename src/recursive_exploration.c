/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_exploration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:29:38 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/02 14:31:36 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*concat_dir_name(char *previous_dir, char *actual_dir)
{
	char	*dir_name;

	dir_name = ft_strnew(ft_strlen(previous_dir) + ft_strlen(actual_dir) + 2);
	ft_strcat(dir_name, previous_dir);
	ft_strcat(dir_name, "/");
	ft_strcat(dir_name, actual_dir);
	return (dir_name);
}

static char		*get_dir_name(char *path)
{
	char		*name;
	const int	path_len = ft_strlen(path);
	int			i;
	int			j;

	i = path_len - 1;
	while (path[i])
	{
		if (path[i] == '/')
			break ;
		--i;
	}
	name = ft_strnew(path_len - 1 - i);
	j = 0;
	while (path[++i])
		name[j++] = path[i];
	return (name);
}

static t_list	*make_linked_list(DIR *d, char *dir_name)
{
	t_list			*dir_list;
	t_list			*new_dir;
	char			*new_dir_name;
	struct dirent	*dir;

	dir_list = NULL;
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.' && dir->d_type == 4)
		{
			new_dir_name = concat_dir_name(dir_name, dir->d_name);
			new_dir = ft_lstnew(new_dir_name,
				ft_strlen(dir_name) + ft_strlen(dir->d_name) + 2);
			ft_lstadd(&dir_list, new_dir);
			ft_memdel((void**)&new_dir_name);
		}
	}
	return (dir_list);
}

void			explore(char *dir_name)
{
	t_list			*dir_list;
	t_list			*cursor;
	DIR				*d;

	d = opendir(dir_name);
	if (d)
	{
		dir_list = make_linked_list(d, dir_name);
		closedir(d);
		sort_file_list(dir_list);
		cursor = dir_list;
		while (cursor)
		{
			printf("%2$c%1$s:%2$c", cursor->content, 10);
			print_file(cursor->content);
			explore(cursor->content);
			cursor = cursor->next;
		}
		free_linked_list(&dir_list);
	}
	else
		printf("ls: %s: %s%c", get_dir_name(dir_name), strerror(errno), 10);
}

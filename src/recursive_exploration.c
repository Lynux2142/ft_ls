/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_exploration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:29:38 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/16 13:42:31 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static t_list	*make_linked_list(int *flag, DIR *d, char *dir_name)
{
	t_list			*dir_list;
	t_list			*new_dir;
	struct dirent	*dir;
	t_file			*data;

	dir_list = NULL;
	while ((dir = readdir(d)) != NULL)
	{
		if ((dir->d_name[0] != '.' || flag[2]) && dir->d_type == 4
			&& !((dir->d_name[0] == '.' && ft_strlen(dir->d_name) == 1)
			|| (dir->d_name[0] == '.' && dir->d_name[1] == '.'
			&& ft_strlen(dir->d_name) == 2)))
		{
			data = (t_file*)malloc(sizeof(t_file));
			data->name = concat_path_and_file(dir_name, dir->d_name);
			data->stat = (struct stat*)malloc(sizeof(struct stat));
			lstat(data->name, data->stat);
			if (!(new_dir = ft_lstnew(data, sizeof(t_file))))
				exit(42);
			ft_lstadd(&dir_list, new_dir);
			ft_memdel((void**)&data);
		}
	}
	return (dir_list);
}

void			explore(int *flag, char *dir_name)
{
	t_list			*dir_list;
	t_list			*cursor;
	DIR				*d;
	char			*err_file;

	if ((d = opendir(dir_name)))
	{
		dir_list = make_linked_list(flag, d, dir_name);
		closedir(d);
		sort_file_list(flag, dir_list);
		cursor = dir_list;
		while (cursor)
		{
			printf("%2$c%1$s:%2$c", ((t_file*)cursor->content)->name, 10);
			print_file(flag, ((t_file*)cursor->content)->name);
			explore(flag, ((t_file*)cursor->content)->name);
			cursor = cursor->next;
		}
		free_linked_list(&dir_list);
	}
	else
	{
		err_file = get_dir_name(dir_name);
		fprintf(stderr, "ls: %s: %s%c", err_file, strerror(errno), 10);
		free(err_file);
	}
}

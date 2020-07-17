/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_exploration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:29:38 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/17 15:42:23 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			if (!(data = (t_file*)malloc(sizeof(t_file)))
				|| !(data->stat = (struct stat*)malloc(sizeof(struct stat))))
				exit(42);
			data->name = concat_path_and_file(dir_name, dir->d_name);
			lstat(data->name, data->stat);
			if (!(new_dir = ft_lstnew(data, sizeof(t_file))))
				exit(42);
			ft_lstadd(&dir_list, new_dir);
			ft_memdel((void**)&data);
		}
	}
	return (dir_list);
}

static void		print(int *flag, t_file *content)
{
	printf("%2$c%1$s:%2$c", content->name, 10);
	print_file(flag, content->name);
	explore(flag, content->name);
}

void			explore(int *flag, char *dir_name)
{
	t_list			*dir_list;
	t_list			*cursor;
	DIR				*d;

	if ((d = opendir(dir_name)))
	{
		dir_list = make_linked_list(flag, d, dir_name);
		closedir(d);
		sort_file_list(flag, dir_list);
		cursor = dir_list;
		while (cursor)
		{
			print(flag, ((t_file*)cursor->content));
			cursor = cursor->next;
		}
		free_linked_list(&dir_list);
	}
	else
		print_error(dir_name, errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:19:09 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/06 16:34:44 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*make_linked_list(int *flag, DIR *d)
{
	t_list			*file_list;
	t_list			*new_file;
	struct dirent	*dir;
	t_file			*data;

	file_list = NULL;
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.' || flag[2])
		{
			data = (t_file*)malloc(sizeof(t_file));
			data->name = ft_strnew(ft_strlen(dir->d_name));
			ft_strcpy(data->name, dir->d_name);
			if (!(new_file = ft_lstnew(data, sizeof(t_file*))))
				exit(42);
			ft_lstadd(&file_list, new_file);
			ft_memdel((void**)&data);
		}
	}
	return (file_list);
}

void			print_file(int *flag, char *dir_name)
{
	t_list			*file_list;
	t_list			*cursor;
	DIR				*d;

	d = opendir(dir_name);
	if (d)
	{
		file_list = make_linked_list(flag, d);
		closedir(d);
		sort_file_list(flag, file_list);
		cursor = file_list;
		while (cursor)
		{
			printf("%s%c", ((t_file*)cursor->content)->name, 10);
			cursor = cursor->next;
		}
		free_linked_list(&file_list);
	}
}

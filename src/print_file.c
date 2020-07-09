/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:19:09 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/09 15:18:11 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*make_linked_list(int *flag, DIR *d, char *dir_name)
{
	t_list			*file_list;
	t_list			*new_file;
	struct dirent	*dir;
	char			*full_path;
	t_file			*data;

	file_list = NULL;
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.' || flag[2])
		{
			full_path = concat_path_and_file(dir_name, dir->d_name);
			data = (t_file*)malloc(sizeof(t_file));
			data->name = ft_strnew(ft_strlen(dir->d_name));
			data->stat = (struct stat*)malloc(sizeof(struct stat));
			stat(full_path, data->stat);
			ft_memcpy(data->name, dir->d_name, ft_strlen(dir->d_name));
			if (!(new_file = ft_lstnew(data, sizeof(t_file))))
				exit(42);
			ft_lstadd(&file_list, new_file);
			ft_memdel((void**)&data);
			ft_memdel((void**)&full_path);
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
		file_list = make_linked_list(flag, d, dir_name);
		closedir(d);
		sort_file_list(flag, file_list);
		cursor = file_list;
		while (cursor)
		{
			printf( (S_ISDIR(((t_file*)cursor->content)->stat->st_mode)) ? "d" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IRUSR) ? "r" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IWUSR) ? "w" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IXUSR) ? "x" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IRGRP) ? "r" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IWGRP) ? "w" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IXGRP) ? "x" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IROTH) ? "r" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IWOTH) ? "w" : "-");
			printf( (((t_file*)cursor->content)->stat->st_mode & S_IXOTH) ? "x" : "-");
			printf("  ");
			printf("%s%c", ((t_file*)cursor->content)->name, 10);
			cursor = cursor->next;
		}
		free_linked_file_list(&file_list);
	}
}

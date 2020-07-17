/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:19:09 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/17 13:28:16 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*create_name(int *flag, char *full_path, char *file_name)
{
	char	*name;
	char	*buf;
	ssize_t	size;
	int		test;

	if (!(buf = (char*)malloc(sizeof(char) * BUFF_SIZE)))
		exit(42);
	ft_bzero(buf, BUFF_SIZE);
	size = 0;
	if (flag[0])
		size = readlink(full_path, buf, BUFF_SIZE);
	test = ft_strlen(file_name) + ((size > 0) ? (size + 4) : 0);
	if (!(name = ft_strnew(test)))
		exit(42);
	ft_strcat(name, file_name);
	if (size > 0)
	{
		ft_strcat(name, " -> ");
		ft_strcat(name, buf);
	}
	ft_memdel((void**)&buf);
	return (name);
}

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
			if (!(data = (t_file*)malloc(sizeof(t_file)))
				|| !(data->stat = (struct stat*)malloc(sizeof(struct stat))))
				exit(42);
			data->name = create_name(flag, full_path, dir->d_name);
			lstat(full_path, data->stat);
			if (!(new_file = ft_lstnew(data, sizeof(t_file))))
				exit(42);
			ft_lstadd(&file_list, new_file);
			free_data(data, full_path);
		}
	}
	return (file_list);
}

static void		print(t_list *cursor)
{
	while (cursor)
	{
		printf("%s%c", ((t_file*)cursor->content)->name, 10);
		cursor = cursor->next;
	}
}

void			print_file(int *flag, char *dir_name)
{
	t_list	*file_list;
	DIR		*d;

	if ((d = opendir(dir_name)))
	{
		file_list = make_linked_list(flag, d, dir_name);
		closedir(d);
		sort_file_list(flag, file_list);
		if (flag[0])
			full_print(file_list);
		else
			print(file_list);
		free_linked_list(&file_list);
	}
	else
		print_error(dir_name, errno);
}

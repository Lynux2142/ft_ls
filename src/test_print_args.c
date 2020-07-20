/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:43:14 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/20 14:51:17 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		make_file_linked_list(t_list **list, char *file_name)
{
	t_list		*new;
	t_file		*data;

	if (!(data = (t_file*)malloc(sizeof(t_file)))
		|| !(data->name = ft_strnew(sizeof(char) * ft_strlen(file_name)))
		|| !((data->stat = (struct stat*)malloc(sizeof(struct stat)))))
		exit(42);
	ft_strcpy(data->name, file_name);
	lstat(file_name, data->stat);
	if (!(new = ft_lstnew(data, sizeof(t_file))))
		exit(42);
	ft_lstadd(list, new);
	ft_memdel((void**)&data);
}

void		make_dir_linked_list(t_list **list, char *dir_name)
{
	t_list		*new;
	t_file		*data;

	if (!(data = (t_file*)malloc(sizeof(t_file)))
		|| !(data->name = ft_strnew(sizeof(char) * ft_strlen(dir_name)))
		|| !((data->stat = (struct stat*)malloc(sizeof(struct stat)))))
		exit(42);
	ft_strcpy(data->name, dir_name);
	lstat(dir_name, data->stat);
	if (!(new = ft_lstnew(data, sizeof(t_file))))
		exit(42);
	ft_lstadd(list, new);
	ft_memdel((void**)&data);
}

void		make_err_linked_list(t_list **list, char *name)
{
	t_list		*new;
	t_file		*data;

	if (!(data = (t_file*)malloc(sizeof(t_file)))
		|| !(data->name = ft_strnew(sizeof(char) * ft_strlen(name) + 34))
		|| !((data->stat = (struct stat*)malloc(sizeof(struct stat)))))
		exit(42);
	ft_strcpy(data->name, "ft_ls: ");
	ft_strcat(data->name, name);
	ft_strcat(data->name, ": No such file or directory");
	data->stat = NULL;
	if (!(new = ft_lstnew(data, sizeof(t_file))))
		exit(42);
	ft_lstadd(list, new);
	ft_memdel((void**)&data);
}

static int	get_nb_file(t_list *err_list, t_list *file_list, t_list *dir_list)
{
	int i;

	i = 0;
	while (err_list)
	{
		++i;
		err_list = err_list->next;
	}
	while (file_list)
	{
		++i;
		file_list = file_list->next;
	}
	while (dir_list)
	{
		++i;
		dir_list = dir_list->next;
	}
	return (i);
}

void		start_print(int *flag, t_list *err_list,
	t_list *file_list, t_list *dir_list)
{
	int	nb_file;

	nb_file = get_nb_file(err_list, file_list, dir_list);
	sort_file_list(flag, err_list);
	sort_file_list(flag, file_list);
	sort_file_list(flag, dir_list);
	while (err_list)
	{
		printf("%s\n", ((t_file*)err_list->content)->name);
		err_list = err_list->next;
	}
	(flag[0]) ? full_print(file_list) : print_files(file_list);
	printf((file_list && dir_list) ? "\n" : "");
	while (dir_list)
	{
		if (nb_file > 1)
			printf("%s:%c", ((t_file*)dir_list->content)->name, 10);
		print_file(flag, ((t_file*)dir_list->content)->name);
		if (flag[1])
			explore(flag, ((t_file*)dir_list->content)->name);
		if (dir_list->next)
			printf("\n");
		dir_list = dir_list->next;
	}
}

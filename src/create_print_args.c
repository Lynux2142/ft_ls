/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_print_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:43:14 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/21 15:34:13 by lguiller         ###   ########.fr       */
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

static void	print_dir(int *flag, t_list *dir_list, int nb_file)
{
	if (nb_file > 1)
	{
		ft_putstr(((t_file*)dir_list->content)->name);
		ft_putendl(":");
	}
	print_file(flag, ((t_file*)dir_list->content)->name);
	if (flag[1])
		explore(flag, ((t_file*)dir_list->content)->name);
	if (dir_list->next)
		ft_putstr("\n");
}

void		start_print(int *flag, t_list *err_list,
	t_list *file_list, t_list *dir_list)
{
	int	nb_file;

	nb_file = list_len(err_list) + list_len(file_list) + list_len(dir_list);
	sort_file_list(flag, err_list);
	sort_file_list(flag, file_list);
	sort_file_list(flag, dir_list);
	while (err_list)
	{
		ft_putendl(((t_file*)err_list->content)->name);
		err_list = err_list->next;
	}
	if (flag[0])
		full_print(file_list);
	else
		print_files(file_list);
	ft_putstr((file_list && dir_list) ? "\n" : "");
	while (dir_list)
	{
		print_dir(flag, dir_list, nb_file);
		dir_list = dir_list->next;
	}
}

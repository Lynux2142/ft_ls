/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:00:58 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/17 16:23:06 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	make_file_linked_list(t_list **list, char *file_name)
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

static void	make_dir_linked_list(t_list **list, char *dir_name)
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

static void	make_err_linked_list(t_list **list, char *name)
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

static void	start_print(int *flag, t_list *err_list,
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
	if (flag[0])
		full_print(file_list);
	else
		print_files(file_list);
	if (file_list && dir_list)
		printf("\n");
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

static void	test_and_print_file(int *flag, char **files)
{
	struct stat	stat;
	int			i;
	t_list		*file_list;
	t_list		*dir_list;
	t_list		*err_list;

	file_list = NULL;
	dir_list = NULL;
	err_list = NULL;
	i = -1;
	while (files[++i])
	{
		lstat(files[i], &stat);
		if (!access(files[i], F_OK))
		{
			if (S_ISDIR(stat.st_mode))
				make_dir_linked_list(&dir_list, files[i]);
			else
				make_file_linked_list(&file_list, files[i]);
		}
		else
			make_err_linked_list(&err_list, files[i]);
	}
	start_print(flag, err_list, file_list, dir_list);
}

int			main(int ac, char **av)
{
	char		*dir_name;
	int			*flag;
	int			i;

	flag = get_flag(av);
	i = 1;
	while (av[i] && av[i][0] == '-' && ft_strlen(av[i]) > 1)
		++i;
	if (ac == i)
	{
		if (!(dir_name = ft_strnew(1)) || !ft_strcat(dir_name, DEFAULT_PATH))
			exit(42);
		print_file(flag, dir_name);
		if (flag[1])
			explore(flag, dir_name);
	}
	else
		test_and_print_file(flag, av + i);
	return (0);
}

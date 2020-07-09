/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:59:20 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/09 15:34:23 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include <errno.h>
# include <sys/stat.h>

# include <stdio.h>

# define DEFAULT_PATH	"."
# define FLAG_LIST		"lRart"

typedef struct			s_file
{
	char				*name;
	struct stat			*stat;
}						t_file;

void					sort_file_list(int *flag, t_list *file_list);
void					print_file(int *flag, char *dir_name);
void					explore(int *flag, char *dir_name);
void					free_linked_file_list(t_list **list);
void					free_linked_dir_list(t_list **list);
int						*get_flag(char **av);
char					*concat_path_and_file(char *path, char *filename);
void					simple_print(t_list *file_list);
void					full_print(t_list *file_list);

#endif

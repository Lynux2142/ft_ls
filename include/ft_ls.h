/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:59:20 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/02 15:39:55 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include <errno.h>

# include <stdio.h>

#define DEFAULT_PATH "."
#define FLAG_LIST "lRart"

void			sort_file_list(int *flag, t_list *file_list);
void			print_file(int *flag, char *dir_name);
void			explore(int *flag, char *dir_name);
void			free_linked_list(t_list **list);
int				*get_flag(char **av);

#endif

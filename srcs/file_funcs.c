/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 00:54:32 by david             #+#    #+#             */
/*   Updated: 2019/08/23 23:18:14 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

struct dirent	*new_file(struct dirent *e)//вот тут создается структура, в которой хранится инфа о файле/папке
{
	struct dirent	*new;

	if (!(new = (struct dirent*)malloc(sizeof(struct dirent))))
		exit (0);
	new->d_ino = e->d_ino;
	new->d_type = e->d_type;
	ft_strcpy(new->d_name, e->d_name);
	return (new);
}

int				append_file(t_files **list, struct dirent *e)//добавляет файл в список
{
	t_files *new;

	if (!(new = (t_files*)malloc(sizeof(t_files))))
		exit (0);
	new->next = NULL;
	new->file = new_file(e);
	if (list[0] == NULL)
	{
		list[0] = new;
		list[1] = new;
	}
	else
	{
		list[1]->next = new;
		list[1] = new;
	}
	return (1);
}

void		free_files(t_files **files)//удаляет список
{
	t_files	*inter;

	while (files[0] != NULL)
	{
		inter = files[0]->next;
		free(files[0]->file);
		free(files[0]);
		files[0] = inter;
	}
}

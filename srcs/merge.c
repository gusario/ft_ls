/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 23:45:30 by david             #+#    #+#             */
/*   Updated: 2019/10/10 00:15:17 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

static void util_free(struct stat *go1, struct stat *go2, char* a, char *b)
{
    free(go1);
    free(go2);
    free(a);
    free(b);
}

static int merge_by_time(t_files *first, t_files *second, char *folder)
{
    struct stat		*govno1;
	struct stat		*govno2;
    int i;
    char *first_path;
    char *second_path;
    
    first_path = ft_strjoin(folder, first->file->d_name);
    second_path = ft_strjoin(folder, second->file->d_name);
    govno1 = (struct stat*)malloc(sizeof(struct stat));
	govno2 = (struct stat*)malloc(sizeof(struct stat));
	lstat(first_path, govno1);
	lstat(second_path, govno2);
	i = (govno1->st_mtimespec.tv_sec - govno2->st_mtimespec.tv_sec);
	if (i == 0)
	{
	    i = (govno1->st_mtimespec.tv_nsec - govno2->st_mtimespec.tv_nsec);
		if (i == 0)
			i = ft_strcmp(second->file->d_name, first->file->d_name);
	}
	i = -i;
    util_free(govno1, govno2, first_path, second_path);
    return(i);
}

static void util_2(t_files *first, t_files *second, t_files	*last)
{
    while (first || second)
	{
		last->next = first == NULL ? second : first;
		last = last->next;
		if (first)
			first = first->next;
		else
			second = second->next;
	}
}

t_files		*merge(t_files *first, t_files *second, t_flags *flg, char *folder)
{
	t_files			*res;
	int				i;
	t_files			*last;
	t_files			*curr;
	
	res = NULL;
    last = NULL;
	while (first && second)
	{
		if (flg->t == 1)
            i = merge_by_time(first, second, folder);
		else
			i = ft_strcmp(first->file->d_name, second->file->d_name);
		if (flg->r == 1)
			i = -i;
		curr = i < 0 ? first : second;
		if (i < 0)
			first = first->next;
		else
			second = second->next;
		if (res == NULL)
		{
			res = curr;
			last = curr;
		}
		else
		{
			last->next = curr;
			last = last->next;
		}
	}
    util_2(first, second, last);
	return (res);
}

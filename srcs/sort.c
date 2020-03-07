/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:04:50 by sbrella           #+#    #+#             */
/*   Updated: 2019/09/13 11:59:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

int			list_length(t_files *list)
{
	int				count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

int			part(t_files **first, t_files **second, t_files *list, int i)
{
	int				ret;

	i = i / 2;
	ret = i;
	*first = list;
	while (i--)
	{
		if (!i)
		{
			*second = list->next;
			list->next = NULL;
			 return (ret);
		}
		list = list->next;
	}
	return (ret);
}

//old merge here

// t_files		*merge(t_files *first, t_files *second, t_flags *flg, char *folder)
// {
// 	t_files			*res;
// 	int				i;
// 	t_files			*last;
// 	t_files			*curr;
// 	struct stat		*govno1;
// 	struct stat		*govno2;
	
// 	res = NULL;
// 	while (first && second)
// 	{
// 		if (flg->t == 1)
// 		{
// 			govno1 = (struct stat*)malloc(sizeof(struct stat));//leak
// 			govno2 = (struct stat*)malloc(sizeof(struct stat));//leak
// 			lstat(ft_strjoin(folder, first->file->d_name), govno1);//leak
// 			lstat(ft_strjoin(folder, second->file->d_name), govno2);//leak
// 			i = (govno1->st_mtimespec.tv_sec - govno2->st_mtimespec.tv_sec);
// 			if (i == 0)
// 			{
// 				i = (govno1->st_mtimespec.tv_nsec - govno2->st_mtimespec.tv_nsec);
// 				if (i == 0)
// 					i = ft_strcmp(second->file->d_name, first->file->d_name);
// 			}
// 			i = -i;
// 		}
// 		else
// 			i = ft_strcmp(first->file->d_name, second->file->d_name);
// 		if (flg->r == 1)
// 			i = -i;
// 		curr = i < 0 ? first : second;
// 		if (i < 0)
// 			first = first->next;
// 		else
// 			second = second->next;
// 		if (res == NULL)
// 		{
// 			res = curr;
// 			last = curr;
// 		}
// 		else
// 		{
// 			last->next = curr;
// 			last = last->next;
// 		}
// 	}
// 	while (first || second)
// 	{
// 		last->next = first == NULL ? second : first;
// 		last = last->next;
// 		if (first)
// 			first = first->next;
// 		else
// 			second = second->next;
// 	}
// 	return (res);
// }

t_files		*merge_sort(t_files *list, t_flags *flg, int i, char *folder)
{
	t_files			*first;
	t_files			*second;
	int				first_i;

	if (i <= 1)
	{
		list->next = NULL;
		return (list);
	}
	first_i = part(&first, &second, list, i);
	first = merge_sort(first, flg, first_i, folder);
	second = merge_sort(second, flg, i - first_i, folder);
	return (merge(first, second, flg, folder));
}

t_files		*sort_list(t_files *list, t_flags *flg, char *folder)
{
	int				i;

	if (!list)
		return (NULL);
	i = list_length(list);
	return (merge_sort(list, flg, i, folder));
}

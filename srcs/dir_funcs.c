/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 01:01:50 by david             #+#    #+#             */
/*   Updated: 2019/10/10 01:31:15 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"
#define BUFFA_SIZE 100

char		*combine_dirs(char *first, char *second)//обЪединяет пути
{
	char	*ptr;
	char	*inptr;

	inptr = ft_strjoin(first, "/");
	ptr = ft_strjoin(inptr, second);
	free(inptr);
	return (ptr);
}

static int ft_check_link(char *path, char *buff)
{
	size_t read;
	// char buff[BUFFA_SIZE + 1];
	ft_bzero(buff, BUFFA_SIZE);
	// buff[0] = '\0';
	if (readlink(path, buff, BUFF_SIZE) == -1)
		return (0);
	if ((read = readlink(path, buff, BUFF_SIZE)) > 0)
	{
		buff[read] = '\0';
		return (1);
	}
	return (0);	
}

static void read_printer(char *av, t_files *inter, t_flags *flg)
{
	char *str;
	char buff[BUFFA_SIZE + 1];
	
	count_staff(av, inter, flg);
	if (flg->l != 0 || flg->n)
		printf("total: %d\n", flg->blocks);
    while (inter != NULL)
	{
		if ((inter->file->d_name[0] == '.') && (flg->a == 0))
		{
			inter = inter->next;
			continue;
		}
		if (flg->i != 0)
		{
			put_space(flg->max_inodes - num_leno(inter->file->d_ino));
			printf("%llu ", inter->file->d_ino);
		}
		if (flg->n != 0 || flg->l != 0)
		{
			str = combine_dirs(av, inter->file->d_name);
			print_stat(str, flg);
			free(str);
		}
		if (ft_check_link(str, buff) == 0)
			printf("%s\n", inter->file->d_name);
		else
			printf("%s -> %s\n", inter->file->d_name, buff);
		inter = inter->next;
	}
}

static void show_subdir(char *av, t_files *inter, t_flags *flg)
{
    char *ptr;
    
    while (inter != NULL)
		{
			if ((flg->a == 0 && inter->file->d_name[0] == '.')
			|| (inter->file->d_name[0] == '.' && inter->file->d_name[1] == '.')
			|| (inter->file->d_name[0] == '.' && inter->file->d_name[1] == '\0'))
			{
				inter = inter->next;
				continue;
			}
			if (inter->file->d_type == DT_DIR)
			{
				read_dir((ptr = combine_dirs(av, inter->file->d_name)), flg);
				free(ptr);
			}
			inter = inter->next;
		}
}

void		read_dir(char *av, t_flags *flg)
{
	DIR				*E;
	struct dirent	*e;
	t_files			*list[2];
	t_files			*inter;
	static int		count = 0;
	
	list[0] = NULL;
	list[1] = NULL;
	if((E = opendir(av)) == NULL)
	{
		terminate(ft_strjoin("\nls: ", &av[norm_name(av)]), flg->R != 0 ? 0 : 1);
		return ;
	}
	if (flg->R != 0 && count++ != 0)
		printf("\n%s:\n", av);
	while ((e = readdir(E)) != NULL)
		append_file(list, e);
	list[0] = sort_list(list[0], flg, av);
	inter = list[0];
	read_printer(av, inter, flg);
	if (flg->R != 0)
	{
		inter = list[0];
		show_subdir(av, inter, flg);
	}
	free_files(list);
	closedir(E);
}
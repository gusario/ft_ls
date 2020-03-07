/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_staff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 23:01:22 by david             #+#    #+#             */
/*   Updated: 2019/10/10 00:15:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

static void count_strings_len(struct stat stat_2, t_flags *flg)
{
    struct passwd	*usuid;
	struct group	*grgid;

    usuid = getpwuid(stat_2.st_uid);
	grgid = getgrgid(stat_2.st_gid);
    if ((int)ft_strlen(usuid->pw_name) > flg->max_pw_name)
		flg->max_pw_name = ft_strlen(usuid->pw_name);
	if ((int)ft_strlen(grgid->gr_name) > flg->max_gr_name)
		flg->max_gr_name = ft_strlen(grgid->gr_name);
}

static void count_num_len(struct stat stat_2, t_flags *flg)
{
    if (num_len(stat_2.st_nlink) > flg->max_nlink)
		flg->max_nlink = num_len(stat_2.st_nlink);
	if (num_len(stat_2.st_uid) > flg->max_uid)
	    flg->max_uid = num_len(stat_2.st_uid);
	if (num_len(stat_2.st_gid) > flg->max_gid)
		flg->max_gid = num_len(stat_2.st_gid);
	if (num_len(stat_2.st_size) > flg->max_size)
		flg->max_size = num_len(stat_2.st_size);
	if (num_len(stat_2.st_ino) > flg->max_inodes)
		flg->max_inodes = num_leno(stat_2.st_ino);
}

void count_staff(char *av, t_files *inter, t_flags *flg)
{
	struct stat stat_2;
	char *str;
	
	while (inter != NULL)
	{
		str = combine_dirs(av, inter->file->d_name);
		lstat(str, &stat_2);
		free(str);
		if (flg->a == 0 && inter->file->d_name[0] == '.')
		{
			inter = inter->next;
			continue;
		}
        count_num_len(stat_2, flg);
        count_strings_len(stat_2, flg);
		flg->blocks += stat_2.st_blocks;
		inter = inter->next;	
	}
}

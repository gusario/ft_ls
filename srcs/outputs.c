/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 23:21:31 by david             #+#    #+#             */
/*   Updated: 2019/10/11 14:45:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

static void flag_n_stats_print(struct stat stat_2, t_flags *flg)
{
    printf("%u", stat_2.st_uid);
	put_space(flg->max_uid - num_len(stat_2.st_uid) + 1);
	printf(" %u", stat_2.st_gid);
	put_space(flg->max_gid - num_len(stat_2.st_gid));
	put_space(flg->max_size - num_len(stat_2.st_size));
	printf("  %lld ", stat_2.st_size);
}

static void flag_l_stats_print(struct stat stat_2, t_flags *flg)
{
    struct passwd	*usuid;
	struct group	*grgid;

    usuid = getpwuid(stat_2.st_uid);
	grgid = getgrgid(stat_2.st_gid);
	printf("%s", usuid->pw_name);
	put_space(flg->max_pw_name - ft_strlen(usuid->pw_name));
	printf("  %s", grgid->gr_name);
	put_space(flg->max_gr_name - ft_strlen(grgid->gr_name));
	put_space(flg->max_size - num_len(stat_2.st_size));
	printf("  %lld ", stat_2.st_size);
//	printf("\tdev == %d,  %d\t", major(stat_2.st_rdev), minor(stat_2.st_rdev));
}

void			print_stat(char *av, t_flags *flg)//чтобы изменить форматирование -l, смотри сюда на принтф
{
	struct stat		stat_2;
	// struct stat		stat_3;

	lstat(av, &stat_2);
	// stat(av, &stat_3);
	print_permission(stat_2.st_mode);
	put_space(flg->max_nlink - num_len(stat_2.st_nlink));
	printf("%hu ", stat_2.st_nlink); 
	if (flg->n != 0)
        flag_n_stats_print(stat_2, flg);
	else
        flag_l_stats_print(stat_2, flg);
	time_print(stat_2);
}
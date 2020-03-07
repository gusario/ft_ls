/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:04:35 by sbrella           #+#    #+#             */
/*   Updated: 2019/10/10 01:06:29 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

void		my_ls(char *argv, t_flags flg, int val)//парсит аргумент
{
	int			err;
	struct stat	stat_1;
	char *str;

	if (*argv != '-' || val > 1)
	{
		if (!(err = lstat(argv, &stat_1)))
		{
			if (S_ISDIR(stat_1.st_mode) && flg.d == 0)
				read_dir(argv, &flg);
			else
			{
				if (flg.i != 0)
				{
					put_space(flg.max_inodes - num_leno(stat_1.st_ino));
					printf("%llu ", stat_1.st_ino);
				}
				if (flg.n != 0 || flg.l != 0)
					print_stat(argv, &flg);
				printf("%s\n", argv);
			}
		}
		else
		{
			str = combine_dirs("ls: ", argv);
			perror(str);
		}
	}
}

int			main( int argc, char **argv)
{
	char	**ptr;
	int		val;
	int		arc;
	t_flags	flg;

	val = 1;
	ptr = argv;
	arc = parse(ptr, argc, &flg);
	if ((arc = arc + 1 - argc) == 0)
		my_ls(".", flg, val);
	else
		while (val < argc)
		{
			my_ls(argv[val], flg, val);
			val++;
		}
	return (0);
}

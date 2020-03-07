/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 21:34:38 by srobert-          #+#    #+#             */
/*   Updated: 2019/09/13 11:52:37 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

static void		print_permissions(mode_t mode)
{
	printf((mode & S_IRUSR) ? "r" : "-");
	printf((mode & S_IWUSR) ? "w" : "-");
	if (mode & S_ISUID)
		printf((mode & S_IXUSR) ? "s" : "S");
	else
		printf((mode & S_IXUSR) ? "x" : "-");
	printf((mode & S_IRGRP) ? "r" : "-");
	printf((mode & S_IWGRP) ? "w" : "-");
	if (mode & S_ISGID)
		printf((mode & S_IXGRP) ? "s" : "S");
	else
		printf((mode & S_IXGRP) ? "x" : "-");
	printf((mode & S_IROTH) ? "r" : "-");
	printf((mode & S_IWOTH) ? "w" : "-");
	if (mode & S_ISVTX)
		printf((mode & S_IXUSR) ? "t " : "T ");
	else
		printf((mode & S_IXOTH) ? "x " : "- ");
}

void print_permission(mode_t mode)
{
    if ((mode & S_IFMT) == S_IFREG)
		printf("-");
	else if ((mode & S_IFMT) == S_IFSOCK)
		printf("s");
	else if ((mode & S_IFMT) == S_IFLNK)
		printf("l");
	else if ((mode & S_IFMT) == S_IFCHR)
		printf("c");
	else if ((mode & S_IFMT) == S_IFBLK)
		printf("b");
	else if ((mode & S_IFMT) == S_IFIFO)
		printf("f");
	else if ((mode & S_IFMT) == S_IFDIR)
		printf("d");
	print_permissions(mode);
}

void time_print(struct stat stat_2)
{
    char *s;

    s = ctime(&stat_2.st_mtime) + 8;
    printf("%.2s ", s);
    printf("%.3s", s - 4);
	if (time(0) - stat_2.st_mtimespec.tv_sec < SIX_MONTHS)
    	printf("%.6s ", s + 2);
	else
		printf(" %.5s ", s + 11);
}

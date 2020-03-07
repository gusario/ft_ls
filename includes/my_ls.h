/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:54:48 by sbrella           #+#    #+#             */
/*   Updated: 2019/10/10 01:28:58 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_LS_H
# define MY_LS_H

# define SIX_MONTHS 15552000
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include "../libft/libft.h"

typedef struct		s_files
{
	struct dirent	*file;
	struct s_files	*next;
}					t_files;

typedef struct		s_flags
{
	int				R;
	int				r;
	int				d;
	int				l;
	int				a;
	int				n;
	int				i;
	int				t;
	int				max_nlink;
	int				max_uid;
	int				max_gid;
	int				max_size;
	int				max_pw_name;
	int				max_gr_name;
	int				max_inodes;
	int				blocks;
}					t_flags;

void				parse_line(char *pntr, t_flags *flg);
void				init_flags(t_flags *flg);
int					parse(char **pntr, int ac, t_flags *flg);
t_files				*sort_list(t_files *list, t_flags *flg, char *folder);
void				permission_print(struct stat stat_2);
void				time_print(struct stat stat_2);
void				print_permission(mode_t mode);
struct dirent	*new_file(struct dirent *e);
int				append_file(t_files **list, struct dirent *e);
void		free_files(t_files **files);
void			print_stat(char *av, t_flags *flg);
void		read_dir(char *av, t_flags *flg);
char		*combine_dirs(char *first, char *second);
void	terminate(char *s, int to_exit);
void put_space(int num);
int num_len(int num);
int num_leno(long long int number);
int norm_name(char *str);
void count_staff(char *av, t_files *inter, t_flags *flg);
t_files		*merge(t_files *first, t_files *second, t_flags *flg, char *folder);
#endif

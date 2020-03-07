/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:28:40 by sbrella           #+#    #+#             */
/*   Updated: 2019/10/10 01:29:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_ls.h"

void	parse_line(char *pntr, t_flags *flg)
{
	int count;
	int flag;

	count = 0;
	flag = 0;
	while (pntr[count] != '\0')
	{
		if (pntr[count] == 'R')
			flg->R = 1;
		else if (pntr[count] == 'd')
			flg->d = 1;
		else if (pntr[count] == 'r')
			flg->r = 1;
		else if (pntr[count] == 'l')
			flg->l = 1;
		else if (pntr[count] == 'a')
			flg->a = 1;
		else if (pntr[count] == 'n')
			flg->n = 1;
		else if (pntr[count] == 'i')
			flg->i = 1;
		else if (pntr[count] == 't')
			flg->t = 1;
		else if (pntr[count] == '-')
		{
			if (count > 0)
				flag = 1;
		}
		else
			terminate(ft_strjoin(ft_strjoin("ls: illegal option -- ", &pntr[count]),
			"\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"), 1);
		count++;
		if (flag == 1 && ft_strcmp(pntr, "--") != 0)
			terminate(ft_strjoin("ls: illegal option -- -",
			"\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"), 1);
	}
}

void	init_flags(t_flags *flg)
{
	flg->R = 0;
	flg->d = 0;
	flg->l = 0;
	flg->a = 0;
	flg->n = 0;
	flg->i = 0;
	flg->t = 0;
	flg->r = 0;
	flg->max_gid = 0;
	flg->max_gr_name = 0;
	flg->max_nlink = 0;
	flg->max_pw_name = 0;
	flg->max_size = 0;
	flg->max_uid = 0;
	flg->blocks = 0;
	flg->max_inodes = 0;
}

int		parse(char **pntr, int ac, t_flags *flg)
{
	int value;
	int nmbr;

	value = 1;
	nmbr = 0;
	init_flags(flg);
	while (value < ac && pntr[value][0] == '-')
	{
		nmbr++;
		parse_line(pntr[value], flg);
		value++;
	}
	return (nmbr);
}

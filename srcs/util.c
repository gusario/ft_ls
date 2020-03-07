/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 01:46:46 by david             #+#    #+#             */
/*   Updated: 2019/10/10 01:27:56 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "my_ls.h"

void	terminate(char *s, int to_exit)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	if (to_exit)
		exit(1);
}

void put_space(int num)
{
	while (num-- > 0)
	{
		printf(" ");
	}
}

int num_len(int number)
{
	int count;
	long long num;
	
	count = 0;
	num = number;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int num_leno(long long int number)
{
	int count;
	long long int num;
	
	count = 0;
	num = number;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int norm_name(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str[i] != '/' && i > 0)
		i--;
	return (i + 1);
}

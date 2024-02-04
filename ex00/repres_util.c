/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repres_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:07:11 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 17:49:28 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// L = max number of lines in dict
#define L 1024
// C = max number of chars in each line
#define C 1024

#include <stdio.h>

int		is_included(char *num_str, char d_n[L][C], int size);

// return a word like 100000000 with digit_n number of digits if included
int	get_word(int digit_n, char d_n[L][C], int size, char c)
{
	int		i;
	char	temp[C];

	temp [0] = c;
	i = 1;
	while (i < digit_n)
	{
		temp[i] = '0';
		i++;
	}
	temp[i] = '\0';
	return (is_included(temp, d_n, size));
}

// returns 1 if the value is one or more zeros in the row ex. 0000
int	is_zero(char *num_str)
{
	int	i;
	int	result;

	i = 0;
	result = num_str[0] == '0';
	while (num_str[i] != '\0')
	{
		if (num_str[i] != '0')
			return (0);
		i++;
	}
	return (result);
}

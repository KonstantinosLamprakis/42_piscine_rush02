/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repres_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:07:11 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 20:51:37 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

// str: a string containing the number
// returns a new string with malloc or NULL in error
// errors : malloc, multiple signs, negative number, chars before number
char	*represent_number(char *str)
{
	int		start;
	int		end;
	int		sign;
	char	*num_str;

	sign = 1;
	start = skip_preffix(str, &sign);
	if (sign == -1)
		return (NULL);
	end = skip_suffix(str, start);
	if (end < start)
		return (NULL);
	num_str = malloc(((end - start + 2) * sizeof(char)));
	ft_copy_string(str, start, end, num_str);
	return (num_str);
}

char	*check_zero(char dic[2][L][C], int size, char *result)
{
	int	i;

	i = is_included("0", dic[0], size);
	if (i == -1)
		return (NULL);
	ft_str_append(result, dic[1][i]);
	return (result);
}

int	print_unit(char *num_str, char dic[2][L][C], int size, char *result)
{
	int	k;
	int	result_length;
	int	digit_n;
	int	i;

	digit_n = ft_strlen(num_str);
	result_length = ft_strlen(result);
	i = put_digits(num_str, dic, size, result);
	if (i == -1)
		return (-1);
	num_str += i;
	if (digit_n > 3 && result_length < ft_strlen(result))
	{
		k = get_word(ft_strlen(num_str) + 1, dic[0], size, '1');
		if (k != -1)
			ft_str_append(result, dic[1][k]);
		else
			return (-1);
	}
	return (i);
}

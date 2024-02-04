/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   representation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:45:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 19:29:52 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check if zero or multiple zeros and just print zero
// 1. check if exists as it is and printed
// 2. check if begins with zero and if yes, skip and go to the next digit
// 3. if mod 3 == 0 -> print it as first three + description(ex. thousand)
	//go on to the next
// 4. if mod 3 == 2 -> print it as first two + description(ex. thousand)
	// go on to the next
// 	4.1. less that 2 digits you print only the description ex. twenty
// 5. if mod 3 == 1 -> print first digit + description(ex. thousand)
	//go on to the next
// 6. go to the next digit and repeat

#include "header.h"

// return a string that represent the single digit num_str[0]
// not usefull for zero
// returns NULL if not exist representation on dict
char	*print_1_d(char num_str, char dic[2][L][C], int size, char *result)
{
	int		i;
	char	temp[2];

	temp[0] = num_str;
	temp[1] = '\0';
	if (num_str == '0')
		return (result);
	i = is_included(temp, dic[0], size);
	if (i != -1)
		return (ft_str_append(result, dic[1][i]));
	return (NULL);
}

char	*print_2_d(char *num_str, char dic[2][L][C], int size, char *result)
{
	int		i;
	char	*temp;
	char	*sub_str;

	if (num_str[0] == '0')
		return (print_1_d(num_str[1], dic, size, result));
	if (ft_strlen(num_str) < 2)
		return (print_1_d(num_str[0], dic, size, result));
	sub_str = ft_copy_string(num_str, 0, 1);
	i = is_included(sub_str, dic[0], size);
	if (i != -1)
		return (ft_str_append(result, dic[1][i]));
	i = get_word(2, dic[0], size, num_str[0]);
	if (i != -1)
		ft_str_append(result, dic[1][i]);
	else
		return (NULL);
	temp = print_1_d(sub_str[1], dic, size, result);
	if (!temp)
		return (NULL);
	return (result);
}

char	*print_3_d(char *num_str, char dic[2][L][C], int size, char *result)
{
	int		i;
	char	*temp;
	char	*sub_str;

	if (num_str[0] == '0')
		return (print_2_d(num_str + 1, dic, size, result));
	if (ft_strlen(num_str) < 3)
		return (print_2_d(num_str, dic, size, result));
	temp = print_1_d(num_str[0], dic, size, result);
	if (!temp)
		return (NULL);
	sub_str = ft_copy_string(num_str, 0, 2);
	i = get_word(3, dic[0], size, '1');
	if (i != -1)
		ft_str_append(result, dic[1][i]);
	else
		return (NULL);
	temp = print_2_d(sub_str + 1, dic, size, result);
	if (!temp)
		return (NULL);
	return (result);
}

// returns -1 on error and size of digits printed otherwise
int	put_digits(char *num_str, char dic[2][L][C], int size, char *result)
{
	int	i;

	i = 0;
	if (ft_strlen(num_str) % 3 == 1)
	{
		if (!print_1_d(num_str[0], dic, size, result))
			return (-1);
		i++;
	}
	else if (ft_strlen(num_str) % 3 == 2)
	{
		if (!print_2_d(num_str, dic, size, result))
			return (-1);
		i += 2;
	}
	else
	{
		if (!print_3_d(num_str, dic, size, result))
			return (-1);
		i += 3;
	}
	return (i);
}

// return the number represantation
char	*convert_number(char *num_str, char dic[2][L][C], int size)
{
	char	*result;
	int		k;
	int		i;
	int		result_length;
	int		digit_n;

	result = malloc(C * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	if (is_zero(num_str))
	{
		i = is_included("0", dic[0], size);
		if (i == -1)
			return (NULL);
		ft_str_append(result, dic[1][i]);
		return (result);
	}
	i = 0;
	digit_n = ft_strlen(num_str);
	// TODO check for NULL on the last func... put the below in while
	while (i < digit_n)
	{
		result_length = ft_strlen(result);
		k = put_digits(num_str, dic, size, result);
		if (k == -1)
			return (NULL);
		i += k;
		num_str += k;
		if (digit_n > 3 && result_length < ft_strlen(result))
		{
			k = get_word(ft_strlen(num_str) + 1, dic[0], size, '1');
			if (k != -1)
				ft_str_append(result, dic[1][k]);
			else
			{
				printf("Error. insaficient dict\n");
				return (NULL);
			}
		}
	}
	return (result);
}

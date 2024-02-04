/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   representation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:45:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 17:49:20 by klamprak         ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>

// L = max number of lines in dict
#define L 1024
// C = max number of chars in each line
#define C 1024

// Declarations of the main.c
char	*represent_number(char *str);
// Declarations of the util.c
int		ft_is_equal_str(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_put_str(char *str);
int		ft_is_numeric(char *str);
char	*ft_copy_string(char *str, int start, int end);
// Declarations of the advanced_util.c
int		skip_preffix(char *str, int *sign);
int		skip_suffix(char *str, int index);
// Declarations of the file.c
int		read_dict(char *file, char d_n[L][C], char d_w[L][C], int *size);
// Declarations of the representation.c
int		is_included(char *num_str, char d_n[L][C], int size);
void	ft_str_append(char *dst, char *src);
int		get_word(int digit_n, char d_n[L][C], int size, char c);
int		get_word(int digit_n, char d_n[L][C], int size, char c);
int		is_zero(char *num_str);

// return a string that represent the single digit num_str[0]
// not usefull for zero
// returns NULL if not exist representation on dict
char	*print_1_digit(char num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int		i;
	char	result[2];

	result[0] = num_str;
	result[1] = '\0';
	if (num_str == '0')
		return ("");
	i = is_included(result, d_n, size);
	if (i != -1)
		return (d_w[i]);
	return (NULL);
}

char	*print_2_digits(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int		i;
	char	*temp;
	char	*result;
	char	*sub_str;

	// if start with 0 means its 1 digit
	if (num_str[0] == '0')
		return (print_1_digit(num_str[1], d_n, d_w, size));
	if (ft_strlen(num_str) < 2)
		return (print_1_digit(num_str[0], d_n, d_w, size));
	// check for the whole number
	sub_str = ft_copy_string(num_str, 0, 1);
	i = is_included(sub_str, d_n, size);
	if (i != -1)
		return (d_w[i]);
	// check more general like 20, 30
	result = malloc(C * sizeof(char));
	result[0] = '\0';
	i = get_word(2, d_n, size, num_str[0]);
	if (i != -1)
		ft_str_append(result, d_w[i]);
	else
		return (NULL);
	// print last digit
	temp = print_1_digit(sub_str[1], d_n, d_w, size);
	if (!temp)
		return (NULL);
	ft_str_append(result, temp);
	return (result);
}

char	*print_3_digits(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int		i;
	char	*temp;
	char	*result;
	char	*sub_str;

	result = malloc(C * sizeof(char));
	result[0] = '\0';
	// if start with 0 means its 2 digits
	if (num_str[0] == '0')
		return (print_2_digits(num_str + 1, d_n, d_w, size));
	if (ft_strlen(num_str) < 3)
		return (print_2_digits(num_str, d_n, d_w, size));
	// print first single digit
	temp = print_1_digit(num_str[0], d_n, d_w, size);
	if (!temp)
		return (NULL);
	ft_str_append(result, temp);
	// check for the whole number
	sub_str = ft_copy_string(num_str, 0, 2);
	// check more general like 100
	i = get_word(3, d_n, size, '1');
	if (i != -1)
		ft_str_append(result, d_w[i]);
	else
		return (NULL);
	// print last 2 digits
	temp = print_2_digits(sub_str + 1, d_n, d_w, size);
	if (!temp)
		return (NULL);
	ft_str_append(result, temp);
	return (result);
}

// return the number represantation
char	*convert_number(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	char	*result;
	int		i;
	int		digit_n;
	int		k;
	int		end;
	int		result_length;

	i = 0;
	result = malloc(C * sizeof(char));
	result[0] = '\0';
	if (is_zero(num_str))
	{
		i = is_included("0", d_n, size);
		if (i == -1)
			return (NULL);
		ft_str_append(result, d_w[i]);
		return (result);
	}
	end = ft_strlen(num_str);
	while (i < end)
	{
		result_length = ft_strlen(result);
		digit_n = ft_strlen(num_str);
		if (digit_n % 3 == 1)
		{
			ft_str_append(result, print_1_digit(num_str[0], d_n, d_w, size));
			i++;
			num_str++;
		}
		else if (digit_n % 3 == 2)
		{
			ft_str_append(result, print_2_digits(num_str, d_n, d_w, size));
			i += 2;
			num_str += 2;
		}
		else
		{
			ft_str_append(result, print_3_digits(num_str, d_n, d_w, size));
			num_str += 3;
			i += 3;
		}
		// add unit ex. thousand, million etc.
		if (digit_n > 3 && result_length < ft_strlen(result))
		{
			k = get_word(ft_strlen(num_str) + 1, d_n, size, '1');
			if (k != -1)
				ft_str_append(result, d_w[k]);
			else
			{
				printf("Error. insaficient dict\n");
				return (NULL);
			}
		}
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   representation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:45:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 13:51:21 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// 4
// 10
// 11
// 34
// 123
// 1123
// 34567
// 134567
// 1234111
// 20000002
// 111
// 4.000
// 100.000.000

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
int		ft_atoi(char *str);
int		skip_preffix(char *str, int *sign);
int		skip_suffix(char *str, int index);
// Declarations of the file.c
int		read_dict(char *file, char d_n[L][C], char d_w[L][C], int *size);
// Declarations of the representation.c
int	is_included(char *num_str, char d_n[L][C], int size);

int	get_word(int digit_n, char d_n[L][C], int size, char c);
// append at the end of dst, the src. Both should be null-terminated
void	ft_str_append(char *dst, char *src)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (src[0] == '\0')
		return ;
	while(dst[i] != '\0')
		i++;
	while (src[k] != '\0')
		dst[i++] = src[k++];
	dst[i++] = ' ';
	dst[i] = '\0';
}


char	*print_1_digit(char num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int	i;
	char result[2];

	result[0] = num_str;
	result[1] = '\0';
	if (num_str == '0')
		return "";
	i = is_included(result, d_n, size);
	if (i != -1)
		return (d_w[i]);
	return (NULL);
}

char	*print_2_digits(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int	i;
	char	*temp;
	char	*result;
	char	sub_str[3];

	result = malloc(C * sizeof(char));
	// if start with 0 means its 1 digit
	if (num_str[0] == '0')
	{
		printf("zero here on 2 %s\n", num_str);
		return (print_1_digit(num_str[1], d_n, d_w, size));
	}
	if (ft_strlen(num_str) < 2)
	{
		printf("zero here on 2 %s\n", num_str);
		return (print_1_digit(num_str[0], d_n, d_w, size));
	}
	// check for the whole number
	sub_str[0] = num_str[0];
	sub_str[1] = num_str[1];
	sub_str[2] = '\0';
	i = is_included(sub_str, d_n, size);
	if (i != -1)
		return (d_w[i]);
	// check more general like 20, 30
	result[0] = '\0';
	i = get_word(2, d_n, size, num_str[0]);
	if (i != -1)
		ft_str_append(result, d_w[i]);
	else
	{
		printf("Error21\n");
		exit(0);
	}
	// print last digit
	temp = print_1_digit(sub_str[1], d_n, d_w, size);
	if (!temp)
	{
		printf("Error22\n");
		exit(0);
	}
	ft_str_append(result, temp);
	return (result);
}

char	*print_3_digits(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	int	i;
	char	*temp;
	char	*result;
	char	sub_str[4];

	result = malloc(C * sizeof(char));
	result[0] = '\0';
	// if start with 0 means its 2 digits
	if (num_str[0] == '0')
	{
		printf("zero here on 3 %s\n", num_str);
		return (print_2_digits(num_str + 1, d_n, d_w, size));
	}
	if (ft_strlen(num_str) < 3)
	{
		printf("zero here on 3 %s\n", num_str);
		return (print_2_digits(num_str, d_n, d_w, size));
	}

	// print first single digit
	temp = print_1_digit(num_str[0], d_n, d_w, size);
	if (!temp)
	{
		printf("Error30\n");
		exit(0);
	}
	ft_str_append(result, temp);
	// check for the whole number
	sub_str[0] = num_str[0];
	sub_str[1] = num_str[1];
	sub_str[2] = num_str[2];
	sub_str[3] = '\0';
	i = is_included(sub_str, d_n, size);
	if (i != -1)
	{
		ft_str_append(result, d_w[i]);
		return (result);
	}
	// check more general like 100
	i = get_word(3, d_n, size, '1');
	if (i != -1)
		ft_str_append(result, d_w[i]);
	else
	{
		printf("Error31\n");
		exit(0);
	}
	// print last 2 digits
	temp = print_2_digits(sub_str + 1, d_n, d_w, size);
	if (!temp)
	{
		printf("Error32\n");
		exit(0);
	}
	ft_str_append(result, temp);
	return (result);
}

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

// return the number represantation
char	*convert_number(char *num_str, char d_n[L][C], char d_w[L][C], int size)
{
	// fix 0
	char	*result;
	int	i;
	int	digit_n;
	int	k;
	int	end;
	int	result_length;

	i = 0;
	result = malloc(C * sizeof(char));
	result[0] = '\0';
	if (is_zero(num_str))
	{
		i = is_included("0", d_n, size);
		if (i == -1)
		{
			printf("Error 0\n");
			return NULL;
		}
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
		}else if (digit_n % 3 == 2)
		{
			ft_str_append(result, print_2_digits(num_str, d_n, d_w, size));
			i += 2;
			num_str += 2;
		}else
		{
			ft_str_append(result, print_3_digits(num_str, d_n, d_w, size));
			num_str += 3;
			i += 3;
		}
		// add unit ex. thousand, million etc.
		if (digit_n > 3 && result_length < ft_strlen(result))
		{
			k = get_word(digit_n - (digit_n % 3) + 1, d_n, size, '1');
			if (k != -1)
			{
				ft_str_append(result, d_w[k]);
			}
			else
			{
				printf("Error. insaficient dict\n");
				return (NULL);
			}
		}
	}
	return (result);
}

// return a word like 100000000 with digit_n number of digits if included
int	get_word(int digit_n, char d_n[L][C], int size, char c)
{
	int	i;
	char	temp[digit_n + 1];

	temp [0] = c;
	i = 1;
	while(i < digit_n)
	{
		temp[i] = '0';
		i++;
	}
	temp[i] = '\0';
	return (is_included(temp, d_n, size));
}

// returns index position if num_str included on dict else -1
// stops when reach to stop point
int	is_included(char *num_str, char d_n[L][C], int size)
{
	int	i;

	i = 0;
	while(i < size)
	{
		if (ft_is_equal_str(num_str, d_n[i]))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
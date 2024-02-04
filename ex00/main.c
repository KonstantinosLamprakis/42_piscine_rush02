/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 08:20:39 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO change error messages
// TODO remove uneccesary function
// TODO remove uneccesary lib includes
// TODO free momory
// TODO create .h file maybe

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

int	main(int argc, char *argv[])
{
	char	*filename;
	char	dict_num[L][C];
	char	dict_words[L][C];
	int		size;
	int		number;
	char	*number_str;

	if (argc == 3)
		filename = argv[2];
	else if (argc == 2)
		filename = "numbers.dict";
	else
	{
		ft_put_str("Error. Number of params\n");
		return (0);
	}
	number_str = represent_number(argv[1]);
	if (!number_str)
	{
		ft_put_str("Error. Negative number or empty param\n");
		return (0);
	}
	size = 0;
	if (!read_dict(filename, dict_num, dict_words, &size))
	{
		ft_put_str("Dict Error.\n");
		return (0);
	}
	number = ft_atoi(number_str);
	printf("number: %d\n", number);
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
	if (end <= start)
		return (NULL);
	num_str = ft_copy_string(str, start, end);
	return (num_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 18:53:41 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO change error messages
// TODO remove uneccesary function
// TODO remove uneccesary lib includes
// TODO free momory of ft_copy_string, represent_number, convert_number
// TODO create .h file maybe
// TODO see the case of key-value on different line or missing value
// TODO trim space from output
// TODO don't take in considaration other values except initial ones

#include "header.h"

// dicts[0] = dict for number
// dicts[1] = dict for words
int	main(int argc, char *argv[])
{
	char	*filename;
	char	dicts[2][L][C];
	int		size;
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
	if (!read_dict(filename, dicts[0], dicts[1], &size))
	{
		ft_put_str("Dict Error.\n");
		return (0);
	}
	printf("Before: %s\n", number_str);
	number_str = convert_number(number_str, dicts, size);
	printf("After: %s\n", number_str);
}

// int i = 0;
// while(i < size)
// {
// 	printf("|%s-%s|\n", dict_num[i], dict_words[i]);
// 	i++;
// }
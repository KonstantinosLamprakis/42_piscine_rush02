/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 21:29:01 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO remove uneccesary lib includes
// TODO see the case of key-value on different line or missing value
// TODO don't take in considaration other values except initial ones
// free of momory leaks from represent_number, convert_number

#include "header.h"

// dicts[0] = dict for number
// dicts[1] = dict for words
int	main(int argc, char *argv[])
{
	char	*filename;
	char	dicts[2][L][C];
	int		size;
	char	*number_str;
	char	*result;
	char	v_t[41][100];

	if (argc == 3)
		filename = argv[2];
	else if (argc == 2)
		filename = "numbers.dict";
	else
	{
		ft_put_str("Error\n");
		return (0);
	}
	number_str = represent_number(argv[1]);
	if (!number_str)
	{
		ft_put_str("Error\n");
		return (0);
	}
	size = 0;
	if (!read_dict(filename, dicts[0], dicts[1], &size))
	{
		ft_put_str("Dict Error\n");
		return (0);
	}
	printf("Before: %s\n", number_str);
	result = convert_number(number_str, dicts, size);
	if (!result)
	{
		ft_put_str("Dict Error\n");
		return (0);
	}
	printf("After: %s\n", result);
	free(number_str);
	free(result);
}

	// get_valid_table(v_t);
	// int i = 0;
	// while(i <= 40)
	// {
	// 	printf("%s\n", v_t[i]);
	// 	i++;
	// }
	// exit(0);
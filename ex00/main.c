/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 21:51:37 by klamprak         ###   ########.fr       */
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
	int		i;

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
	get_valid_table(v_t);
	dict_compare(dicts, v_t, size);
	i = 0;
	while (i <= 40)
	{
		printf("%s\n", v_t[i]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		printf("%s->%s\n", dicts[0][i], dicts[1][i]);
		i++;
	}
	exit(0);
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

int	dict_compare(char dicts[2][L][C], char v_t[41][100], int size)
{
	int	i;
	int	k;

	i = 0;
	while (i < size)
	{
		k = is_included_arr(dicts[0][i], v_t, 41);
		if (k == -1)
		{
			dicts[0][i][0] = '\0';
		}
		else
		{
			v_t[k][0] = '\0';
		}
		i++;
	}
	i = 0;
	while (i < 41)
	{
		if (v_t[i][0] == '\0')
			return (-1);
		i++;
	}
	return (1);
}

// returns index position if num_str included on dict else -1
// stops when reach to stop point
int	is_included_arr(char *num_str, char d_n[41][100], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_is_equal_str(num_str, d_n[i]))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

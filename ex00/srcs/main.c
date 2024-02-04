/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 23:05:01 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// free of momory leaks from represent_number, convert_number

#include "header.h"

// dicts[0] = dict for number
// dicts[1] = dict for words
int	main(int argc, char *argv[])
{
	char	dicts[2][L][C];
	int		size;
	char	*number_str;
	char	*result;

	if (init(argc, argv[2], dicts, &size) == -1)
		return (0);
	number_str = represent_number(argv[1]);
	if (!number_str)
	{
		ft_put_str("Error\n");
		return (0);
	}
	result = convert_number(number_str, dicts, size);
	if (!result)
	{
		ft_put_str("Dict Error\n");
		return (0);
	}
	ft_put_str(result);
	ft_put_str("\n");
	free(number_str);
	free(result);
}

int	init(int argc, char *argv, char dicts[2][L][C], int *size)
{
	char	*filename;

	if (argc == 3)
		filename = argv;
	else if (argc == 2)
		filename = "numbers.dict";
	else
	{
		ft_put_str("Error\n");
		return (-1);
	}
	*size = 0;
	if (validate_dict (filename, dicts, size) == -1)
		return (-1);
	return (*size);
}

int	validate_dict(char *filename, char dicts[2][L][C], int *size)
{
	char	v_t[41][100];

	*size = 0;
	if (!read_dict(filename, dicts[0], dicts[1], size))
	{
		ft_put_str("Dict Error\n");
		return (-1);
	}
	get_valid_table(v_t);
	if (dict_compare(dicts, v_t, *size) == -1)
	{
		ft_put_str("Dict Error\n");
		return (-1);
	}
	return (0);
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
		if (v_t[i][0] != '\0')
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

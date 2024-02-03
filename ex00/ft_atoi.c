/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:15:25 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/03 11:55:32 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

int	get_int(char *str, int i, int sign);

// takes a string and returns the integer number
// is_prefix: 1 if need to trim spaces, signs from the beggining
int	ft_atoi(char *str, int is_prefix)
{
	int	i;
	int	t;
	int	sign;

	i = 0;
	t = 1;
	sign = 1;
	if (!is_prefix)
		return (get_int(str, i, sign));
	while (str[i] != '\0')
	{
		t = (str[i] != ' ') && (str[i] != '\n') && (str[i] != '\f');
		t = t && (str[i] != '\v') && (str[i] != '\t') && (str[i] != '\r');
		if (t)
			break ;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	return (get_int(str, i, sign));
}

int	get_int(char *str, int i, int sign)
{
	int	div;
	int	result;
	int	end;
	int	is_error;

	result = 0;
	end = i;
	is_error = 1;
	while (str[end] != '\0' && str[end] >= '0' && str[end] <= '9')
	{
		is_error = 0;
		end++;
	}
	div = 1;
	while (str[end -1] >= '0' && str[end - 1] <= '9')
	{
		is_error = 0;
		result = result - ((str[end - 1] - '0') * div);
		div *= 10;
		end--;
	}
	if (is_error)
		errno = EINVAL;
	return (result * sign * -1);
}

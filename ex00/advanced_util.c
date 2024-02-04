/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:42:53 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 05:51:43 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file contains some functions specialized for this project

#include <errno.h>

// sign = 1 if positive and -1 if negative
// return the integer from string
// return 0 and put errno value in case of empty element
int	ft_atoi(char *str)
{
	int	div;
	int	result;
	int	index;

	result = 0;
	index = 0;
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
		index++;
	div = 1;
	while (str[index -1] >= '0' && str[index - 1] <= '9')
	{
		result = result - ((str[index - 1] - '0') * div);
		div *= 10;
		index--;
	}
	return (result * -1);
}

// trim spaces, signs from the beggining
// put 1 or -1 on sign depends on the number sign
// return the first index of string after the sign
int	skip_preffix(char *str, int *sign)
{
	int	i;
	int	t;

	i = 0;
	*sign = 1;
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
			*sign = -*sign;
		i++;
	}
	return (i);
}

// start from index position and returns the position of last char that is digit
int	skip_suffix(char *str, int index)
{
	while (str[index] != '\0')
	{
		if (!(str[index] >= '0' && str[index] <= '9'))
			return (index - 1);
		index++;
	}
	return (index - 1);
}

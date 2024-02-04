/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:15:25 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/05 00:03:10 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file contains some basic util fanctions

#include "header.h"

// compare 2 strings and return 1 only if they are equal
int	ft_is_equal_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}

// returns a new string with malloc from first str
// start and end are indexes of 1st and last char in str
char	*ft_copy_string(char *str, int start, int end, char *sub_str)
{
	int		i;

	if (end - start < 0)
		return (NULL);
	i = 0;
	while (end - start >= 0)
	{
		sub_str[i] = str[start];
		start++;
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

char	*trim_space(char *str)
{
	int		i;
	int		space_before;
	char	temp[C];
	int		k;

	k = 0;
	i = 0;
	space_before = 1;
	while (str[i] != '\0')
	{
		if (space_before && str[i] != ' ')
			space_before = 0;
		if (!(space_before && str[i] == ' '))
		{
			temp[k++] = str[i];
			i++;
		}
	}
	if (str[i - 1] == ' ')
		temp[k - 1] = '\0';
	else
		temp[k] = '\0';
	str[0] = '\0';
	ft_str_append(str, temp);
	return (str);
}

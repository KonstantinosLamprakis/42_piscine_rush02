/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:15:25 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 08:12:15 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file contains some basic util fanctions

#include <unistd.h>
#include <stdlib.h>

// compare 2 strings and return 0 only if they are equal
int	ft_is_equal_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

// returns a new string with malloc from first str
// start and end are indexes of 1st and last char in str
char	*ft_copy_string(char *str, int start, int end)
{
	char	*result;
	int		i;

	if (end - start < 0)
		return (NULL);
	result = malloc((end - start + 2) * sizeof(char));
	i = 0;
	while (end - start >= 0)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

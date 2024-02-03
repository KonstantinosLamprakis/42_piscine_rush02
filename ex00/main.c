/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:13:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/03 14:50:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO change error messages
// TODO remove uneccesary function

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Declarations of the main.c
int		represent_number(char *str);
// Declarations of the util.c
int		ft_is_equal_str(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_put_str(char *str);
int		ft_is_numeric(char *str);
char	*ft_copy_string(char *str, int start, int end);
// Declarations of the advanced_util.c
int		ft_atoi(char *str, int sign);
int		skip_preffix(char *str, int *sign);
int		skip_suffix(char *str, int index);

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		// TODO read dictionary
		represent_number(argv[1]);
	}
	else if (argc == 2)
	{
		represent_number(argv[1]);
	}
	else
	{
		ft_put_str("Error. Number of params\n");
	}
}

int	represent_number(char *str)
{
	int		start;
	int		end;
	int		sign;
	int		number;
	char	*num_str;

	sign = 1;
	start = skip_preffix(str, &sign);
	printf("start: %d\n", start);
	end = skip_suffix(str, start);
	printf("start: %d\n", end);
	num_str = ft_copy_string(str, start, end);
	printf("final str: %s\n", num_str);
	number = ft_atoi(num_str, sign);
	printf("number: %d\n", number);
	return (0);
}

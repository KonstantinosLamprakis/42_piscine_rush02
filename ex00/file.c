/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:20:35 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 06:31:21 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// L = max number of lines in dict, C = max number of chars in each line
#define L 1024
#define C 1024

// returns 1 if number is space according to isspace(3) and 0 otherwise
int	is_space(char c)
{
	int	t;

	t = (c != ' ') && (c != '\n') && (c != '\f');
	t = t && (c != '\v') && (c != '\t') && (c != '\r');
	return (!t);
}

// return: -1 on error, 0 on success
int	read_dict(char *file, char dict_num[L][C], char dict_words[L][C], int *size)
{
	int	fd;
	ssize_t	bytes_read;
	char	line[2];
	int	k;
	int	is_num_spacebef_nline[3];
	int is_number;
	int is_space_before;
	int is_new_sentense;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	*size = 0;
	k = 0;
	is_num_spacebef_nline[0] = 1;
	is_num_spacebef_nline[1] = 1;
	is_num_spacebef_nline[2] = 1;
	is_number = 1;
	is_space_before = 1;
	is_new_sentense = 1;
	bytes_read = read(fd, line, 1);
	while (bytes_read > 0)
	{
		if (line[0] == '\n' && is_new_sentense)
		{
			bytes_read = read(fd, line, 1);
			continue;
		}
		else if (is_new_sentense && !is_space(line[0]))
			is_new_sentense = 0;
		if (line[0] == ':')
		{
			is_number = 0;
			is_space_before = 1;
			dict_num[*size][k] = '\0';
			k = 0;
			bytes_read = read(fd, line, 1);
			continue;
		}
		if (line[0] == '\n' && !is_number)
		{
			dict_words[*size][k] = '\0';
			(*size)++;
			k = 0;
			is_number = 1;
			is_new_sentense = 1;
			bytes_read = read(fd, line, 1);
			continue;
		}
		if (is_space(line[0]) && is_space_before)
		{
			bytes_read = read(fd, line, 1);
			continue;
		}
		else
			is_space_before = is_space(line[0]);
		if (is_number)
			dict_num[*size][k++] = line[0];
		else
			dict_words[*size][k++] = line[0];
		bytes_read = read(fd, line, 1);
	}
	if (bytes_read == -1)
		return (-1);
	close(fd);
	return (1);
}

// int	read_char(char dict_num[L][C], char dict_words[L][C], int *size, int is_num_spacebef_nline[3])
// {
// 	char	line[2];
// 	int	k;
// }

int main() {
	char	*filename;
	char	dict_num[L][C];
	char	dict_words[L][C];
	int		size;
	int		error;
	int		i;

	filename = "numbers.dict";
	error = read_dict(filename, dict_num, dict_words, &size);
	printf("-1 is error: %d\n", error);
	i = 0;
	while(i < size)
	{
		printf("%s--->%s\n", dict_num[i] ,dict_words[i]);
		i++;
	}
	return (error);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:20:35 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 21:51:17 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// returns 1 if number is space according to isspace(3) and 0 otherwise
int	is_space(char c)
{
	int	t;

	t = (c != ' ') && (c != '\n') && (c != '\f');
	t = t && (c != '\v') && (c != '\t') && (c != '\r');
	return (!t);
}

// returns if a string is a valid dict key
void	get_valid_table(char temp[41][100])
{
	int		t;
	int		i;

	i = 0;
	while (i < 10)
	{
		temp[i][0] = '0' + i;
		temp[i][1] = '\0';
		temp[i + 10][0] = '1';
		temp[i + 10][1] = '0' + i;
		temp[i + 10][2] = '\0';
		i++;
	}
	t = 20;
	i = 2;
	while (i <= 9)
	{
		temp[t][0] = '0' + i;
		temp[t][1] = '0';
		temp[t++][2] = '\0';
		i++;
	}
	put_big_numbers(temp, t);
}

void	put_big_numbers(char temp[41][100], int index)
{
	int	i;
	int	j;
	int	zeros;

	temp[index][0] = '1';
	temp[index][1] = '0';
	temp[index][2] = '0';
	temp[index++][3] = '\0';
	zeros = 4;
	i = 0;
	while (i <= 11)
	{
		j = 1;
		temp[index][0] = '1';
		while (j <= zeros - 1)
		{
			temp[index][j] = '0';
			if (j == zeros)
				temp[index][j + 1] = '\n';
			j++;
		}
		zeros += 3;
		i++;
		index++;
	}
}

// r_c: reads 1 char from dict and put it on d_w, d_n
// returns 1 if put char on dicts or 0 if not
// d_n = dictionary of numbers
// d_w = dictionary of words
// c_j_k = 0 index is the current character on dict
// c_j_k = 1 and 2 indexes are the dict arrays indexes
// is_n_spb_nl = index 0 is_number, 1 is_space_before, 2 is_new_line_sentence
int	r_c(char d_n[L][C], char d_w[L][C], char c_j_k[3], int is_n_spb_nl[3])
{
	if (c_j_k[0] == ':')
	{
		is_n_spb_nl[0] = 0;
		is_n_spb_nl[1] = 1;
		d_n[(int)c_j_k[1]][(int)c_j_k[2]] = '\0';
		c_j_k[2] = 0;
		return (0);
	}
	if (c_j_k[0] == '\n' && !is_n_spb_nl[0])
	{
		d_w[(int)c_j_k[1]++][(int)c_j_k[2]] = '\0';
		c_j_k[2] = 0;
		is_n_spb_nl[0] = 1;
		is_n_spb_nl[2] = 1;
		return (1);
	}
	if (is_space(c_j_k[0]) && is_n_spb_nl[1])
		return (0);
	else
		is_n_spb_nl[1] = is_space(c_j_k[0]);
	if (is_n_spb_nl[0])
		d_n[(int)c_j_k[1]][(int)c_j_k[2]++] = c_j_k[0];
	else
		d_w[(int)c_j_k[1]][(int)c_j_k[2]++] = c_j_k[0];
	return (0);
}

// read_dict: read the dict-file and initialize dict num-words and their size
// return: 0 on error, 1 on success
int	read_dict(char *file, char d_n[L][C], char d_w[L][C], int *size)
{
	int		fd;
	ssize_t	bytes_read;
	char	c_j_k[3];
	int		is_n_spb_nl[3];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	is_n_spb_nl[0] = 1;
	is_n_spb_nl[1] = 1;
	is_n_spb_nl[2] = 1;
	bytes_read = read(fd, c_j_k, 1);
	c_j_k[2] = 0;
	while (bytes_read > 0)
	{
		if (is_n_spb_nl[2] && !is_space(c_j_k[0]) && c_j_k[0] != '\n')
			is_n_spb_nl[2] = 0;
		if (!(c_j_k[0] == '\n' && is_n_spb_nl[2]))
			*size += r_c(d_n, d_w, c_j_k, is_n_spb_nl);
		bytes_read = read(fd, c_j_k, 1);
	}
	if (bytes_read == -1)
		return (0);
	close(fd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:20:35 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 08:18:03 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// L = max number of lines in dict
#define L 1024
// C = max number of chars in each line
#define C 1024

// returns 1 if number is space according to isspace(3) and 0 otherwise
int	is_space(char c)
{
	int	t;

	t = (c != ' ') && (c != '\n') && (c != '\f');
	t = t && (c != '\v') && (c != '\t') && (c != '\r');
	return (!t);
}

// read_char: reads 1 char from dict and put it on d_w, d_n
// returns 1 if put char on dicts or 0 if not
// d_n = dictionary of numbers
// d_w = dictionary of words
// c_j_k = 0 index is the current character on dict
// c_j_k = 1 and 2 indexes are the dict arrays indexes
// is_n_spb_nl = index 0 is_number, 1 is_space_before, 2 is_new_line_sentence
int	read_char(char d_n[L][C], char d_w[L][C], char c_j_k[3], int is_n_spb_nl[3])
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
			*size += read_char(d_n, d_w, c_j_k, is_n_spb_nl);
		bytes_read = read(fd, c_j_k, 1);
	}
	if (bytes_read == -1)
		return (0);
	close(fd);
	return (1);
}

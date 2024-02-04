/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:55:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/02/04 23:04:18 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// L = max number of lines in dict
#define L 1024
// C = max number of chars in each line
#define C 1024

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// declarations of advanced_util.c
int		skip_preffix(char *str, int *sign);
int		skip_suffix(char *str, int index);
char	*ft_str_append(char *dst, char *src);
int		is_included(char *num_str, char d_n[L][C], int size);
void	ft_put_str(char *str);

// declarations of file.c
int		is_space(char c);
int		r_c(char d_n[L][C], char d_w[L][C], char c_j_k[3], int is_n_spb_nl[3]);
int		read_dict(char *file, char d_n[L][C], char d_w[L][C], int *size);
void	get_valid_table(char temp[41][100]);
void	put_big_numbers(char temp[41][100], int index);

// declarations of repres_util.c
int		get_word(int digit_n, char d_n[L][C], int size, char c);
int		is_zero(char *num_str);
char	*represent_number(char *str);
int		print_unit(char *num_str, char dic[2][L][C], int size, char *result);
char	*check_zero(char dic[2][L][C], int size, char *result);

// declarations of util.c
int		ft_is_equal_str(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_copy_string(char *str, int start, int end, char sub_str[3]);
void	ft_put_str(char *str);
char	*trim_space(char *str);

// declarations of representation.c
char	*print_1_d(char num_str, char dic[2][L][C], int size, char *result);
char	*print_2_d(char *num_str, char dic[2][L][C], int size, char *result);
char	*print_3_d(char *num_str, char dic[2][L][C], int size, char *result);
char	*convert_number(char *num_str, char dic[2][L][C], int size);
int		put_digits(char *num_str, char dic[2][L][C], int size, char *result);

// declarations of main.c
int		is_included_arr(char *num_str, char d_n[41][100], int size);
int		dict_compare(char dicts[2][L][C], char v_t[41][100], int size);
int		validate_dict(char *filename, char dicts[2][L][C], int *size);
int		init(int argc, char *argv, char dicts[2][L][C], int *size);
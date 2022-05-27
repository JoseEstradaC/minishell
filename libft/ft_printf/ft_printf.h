/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:23:02 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/10 19:42:16 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

/**
 * 
 * ORDER
 * 
 * aling, plus, space, zeropadding, hashtag, width, precision, type
 * ------------
 * 
 * data  		-> data to print
 * type			-> % value
 * 
 * '0' flag ignored with '-' flag
 * '0' flag ignored with precision
 * 
 * aling		-> 0 default (right-align), 1 (Left-align)
 * zeropadding	-> 0 default, >0 amount of zero padding
 * precision 	-> 0 default, >0 amount of (int zero padding)(s number to print)
 * width		-> 0 default, >0 amount of space (Depend of aling)
 * hashtag		-> 0 default, 1 (in x or X) 0x or 0X suffix
 * space		-> 0 default, 1 (in d or i) if is posivite print ' '
 * plus			-> 0 default, 1 (in d or i) if is posivite print '+'
 * 
*/

typedef struct s_placeholder
{
	char		*data;
	char		type;
	size_t		aling;
	size_t		zeropadding;
	size_t		precision;
	size_t		width;
	size_t		hashtag;
	size_t		space;
	size_t		plus;

}				t_placeholder;

t_placeholder	*ft_printf_analysis(const char **str, va_list *argptr);
int				ft_prinft_analysis_flag_aling(const char **str);
int				ft_prinft_analysis_flag_zeropadding(const char **str);
int				ft_prinft_analysis_flag_plus(const char **str);
int				ft_prinft_analysis_flag_space(const char **str);
int				ft_prinft_analysis_flag_hashtag(const char **str);
int				ft_prinft_analysis_flag_width(const char **str);
int				ft_prinft_analysis_flag_precision(const char **str);
int				ft_prinft_analysis_precision_to_padding(
					t_placeholder *placeholder);
char			*ft_printf_transform_ptr_to_hex(void *ptr);
char			*ft_printf_transform_uint(unsigned int n);
int				ft_recursive_number_ptr(uintptr_t num, char **str);
char			*ft_printf_transform_ptr_to_hex(void *ptr);
char			*ft_printf_analysis_data_s(va_list *argptr, size_t space);
char			*ft_printf_analysis_data_c(va_list *argptr);
int				ft_recursive_number16(unsigned int num, char **str);
char			*ft_printf_transform_uin_to_hex(unsigned int num, int mayus,
					int show0x);
char			*ft_printf_analysis_data_type(char type, va_list *argptr,
					t_placeholder *placeholder);
int				ft_printf_print_plus_space(t_placeholder *analized_placeholder);
int				ft_printf_print_precision(t_placeholder *analized_placeholder);
int				ft_prinft_print_width(t_placeholder *analized_placeholder);
int				ft_printf_print_placeholder(char const **str, va_list *argptr);
int				ft_printf_found_placeholder(char const **str, va_list *argptr);
int				ft_printf_print_placeholder_type_c(t_placeholder *placeholder);
int				ft_printf_print(char const **str, va_list *argptr);
int				ft_printf(char const *org, ...);
size_t			ft_printf_print_width_get(t_placeholder *analized_placeholder);
int				ft_printf_check_fixminus(t_placeholder *analized_placeholder);
int				ft_printf_placeholder_width_write(t_placeholder *placeholder,
					char *padding);

#endif

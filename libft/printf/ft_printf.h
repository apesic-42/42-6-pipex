/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:04:01 by apesic            #+#    #+#             */
/*   Updated: 2024/11/29 14:22:44 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *n, ...);
int		percent_c(int arg);
int		percent_s(char *arg);
int		percent_d(int arg);
int		percent_i(int arg);
int		percent_u(long long arg);

int		percent_p(unsigned long long arg);
int		percent_x(unsigned int arg);
int		percent_xx(unsigned int arg);
int		percent_percent(void);

int		ft_putnumber_u(int a);
char	*ft_itoa_hexa_ll(unsigned long long num);
char	*ft_itoa_hexa(unsigned int n);
char	*ft_itoa_hexa_upper(unsigned int n);

#endif

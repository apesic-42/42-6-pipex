/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:59:56 by apesic            #+#    #+#             */
/*   Updated: 2024/11/11 16:59:59 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* void	exemple(unsigned int ok, char *le)
{
	(void)ok;
	*le -= 32;
}

#include <stdio.h>

int main (int c, char **v)
{
	(void)c;
	char * ok = v[1];
	ft_striteri(ok, exemple);
	printf("ma : %s\n", ok);
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:58:13 by apesic            #+#    #+#             */
/*   Updated: 2024/11/25 15:55:17 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	slen;
	char			*ma;

	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
	{
		ma = malloc(1);
		*ma = 0;
		return (ma);
	}
	slen = (unsigned int)len;
	if ((size_t)ft_strlen(&s[start]) < len)
		slen = ft_strlen(&s[start]);
	ma = malloc(slen + 1);
	if (ma == NULL)
		return (NULL);
	while (i < slen)
	{
		ma[i] = s[i + start];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}
/* int main (int c, char **v)
  #include <stdio.h>
{
	(void)c;
	(void)v;
 	char *str = "lejcles";
    size_t start = 4; 
	//printf("%s\n", &str[start]);
  	printf("%s", ft_substr(str, 4, 123)); 
}   
 */
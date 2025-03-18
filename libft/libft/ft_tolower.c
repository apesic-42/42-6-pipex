/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:55:27 by apesic            #+#    #+#             */
/*   Updated: 2024/11/05 16:57:30 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdlib.h>


int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c += 32);
	return (c);
}

void free_double_table(char **table)
{
    int i;

    i = 0;
    while (table[i])
    {
    	free(table[i]);
    	i++;
    }
    free(table);
}
/* #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int c, char **v)
{
	(void)c;
	printf("%d\n", tolower(v[1][0]));
	printf("%d\n", ft_tolower(v[1][0]));
} */

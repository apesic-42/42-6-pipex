/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:32:38 by apesic            #+#    #+#             */
/*   Updated: 2024/11/13 14:14:41 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == 0 && src == 0)
		return (dest);
	while (n > i)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>
int main ()
{

    //char ok[7] = "okokok";
    //char le[7] = "lelele";

	//char ok2[7] = "okokok";
    //char le2[7] = "lelele";

    //ft_memcpy(ok, le, 1);
	ft_memcpy(((void*)0), ((void*)0), 3);
	//memcpy(ok2, le2, 1);
    //printf("%s\n", ok);
	//printf("%s\n", ok2);
}
 */
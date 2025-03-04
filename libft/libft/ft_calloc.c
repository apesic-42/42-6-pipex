/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:43:56 by apesic            #+#    #+#             */
/*   Updated: 2024/11/25 14:19:19 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	p;
	void	*res;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	p = nmemb * size;
	res = malloc(p);
	if (res == NULL || p / size != nmemb)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}
/* 
#include <stdio.h>
int main ()
{

	int size;
	int count = 42 * 3;

	// malloc(size_t size); 2147483647
	char *res2 = ft_calloc(count, sizeof(char));


	printf("res2 : %s\n", res2);
	free(res2);
} */
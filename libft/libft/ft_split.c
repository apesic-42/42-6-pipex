/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:28:19 by apesic            #+#    #+#             */
/*   Updated: 2024/11/25 15:49:29 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	*clean_exit(char **l, int t)
{
	int	i;

	i = 0;
	while (i < t)
		free(l[i++]);
	free(l);
	return (NULL);
}

static int	count_w(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	place(char const *s, char c)
{
	int	len_mot;

	if (!ft_strchr(s, (unsigned char)c))
		len_mot = ft_strlen(s);
	else
		len_mot = ft_strchr(s, (unsigned char)c) - s;
	return (len_mot);
}

char	**ft_split(char const *s, char c)
{
	char	**l;
	int		t;
	int		len_mot;

	t = 0;
	l = (char **)malloc((count_w(s, c) + 1) * sizeof(char *));
	if (!s || !l)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			len_mot = place(s, c);
			l[t] = ft_substr(s, 0, (size_t)len_mot);
			if (l[t] == NULL)
				return (clean_exit(l, t));
			t++;
			s += len_mot;
		}
	}
	l[t] = NULL;
	return (l);
}
// #include <stdio.h>

// int	main(int c, char **v)
// {
// 	(void)c;
// 	//char **res = ft_split(v[1], v[2][0]);
// 	char **res = ft_split("hello!", ' ');	int i = 0;
// 	while (res[i])
// 	{
// 		printf("res : %s\n", res[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (!res[i])
// 	{
// 		free(res[i]);
// 		i++;
// 	}
// 	free(res);
// } 

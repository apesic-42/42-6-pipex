/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:39:24 by apesic            #+#    #+#             */
/*   Updated: 2024/12/16 16:33:32 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	afficher_liste(t_caract *head)
{
	t_caract	*courant;

	courant = head;
	while (courant != NULL)
	{
		printf("%c>", courant->data);
		courant = courant->next;
	}
	printf("NULL\n");
}

int	len_before_nl(t_caract *first)
{
	int			i;
	t_caract	*courant;

	i = 0;
	courant = first;
	while (courant != NULL)
	{
		if (courant->is_nl == true)
			return (i + 1);
		courant = courant->next;
		i++;
	}
	return (-1);
}

t_caract	*new_t_caract(t_caract *t_caract)
{
	if (t_caract->data == '\n')
		t_caract->is_nl = true;
	else
		t_caract->is_nl = false;
	t_caract->next = NULL;
	return (t_caract);
}

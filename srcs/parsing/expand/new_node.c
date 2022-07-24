/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:22:54 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 23:39:30 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	add_back_new_node(char **insert, t_token *back, t_token *next, int len)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (++i < len)
	{
		tmp = ft_malloc(sizeof(t_token) * (1));
		if (!tmp)
			return ;
		if (back)
			back->next = tmp;
		if (next)
			next->back = tmp;
		tmp->back = back;
		tmp->next = next;
		tmp->type = ARG;
		tmp->word = ft_strdup(insert[i]);
		back = tmp;
	}
}

void	replace_old_node(t_token **old_node, char **to_insert)
{
	int		len;
	t_token	*back;
	t_token	*next;

	len = len_darr(to_insert);
	back = (*old_node)->back;
	next = (*old_node)->next;
	ft_free((*old_node)->word);
	(*old_node)->word = ft_strdup(to_insert[0]);
	if (len > 1)
	{
		back = (*old_node);
		add_back_new_node(to_insert, back, next, len);
	}
}

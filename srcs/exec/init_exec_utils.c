/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:43:56 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 15:47:24 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_node(t_token *token)
{
	int	x;

	x = 0;
	while (token)
	{
		if (token->type == PIPE || !token->next)
			x++;
		token = token->next;
	}
	return (x);
}

t_node	*ft_lstadd_back(t_node *lst, t_node *new)
{
	t_node	*alst;

	alst = lst;
	if (!alst)
		return (new);
	else
	{
		while ((alst)->next)
			alst = (alst)->next;
		(alst)->next = new;
	}
	return (lst);
}

t_token	*go_next(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		token = token->next;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:13 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 15:35:10 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		ft_free(arr[i]);
		arr[i] = NULL;
	}
	ft_free(arr);
	arr = NULL;
}

void	ft_free_node(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->here_doc)
			ft_free(tmp->here_doc);
		ft_free(tmp);
		tmp = NULL;
	}
}

void	ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp && tmp->word)
			ft_free(tmp->word);
		if (tmp)
			ft_free(tmp);
		tmp = NULL;
	}
}

void	clean(t_exec *utils)
{
	if (utils->node)
	{
		ft_free_node(utils->node);
		utils->node = NULL;
	}
	if (utils->token_tmp)
	{
		ft_free_token(utils->token_tmp);
	}
	utils->can_run = 1;
}

void	cleaning_parsing(t_expand *exp, t_quote *state)
{	
	ft_free(exp);
	exp = NULL;
	ft_free(state);
	state = NULL;
}

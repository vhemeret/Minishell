/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:13 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 21:11:47 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
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
			free(tmp->here_doc);
		free(tmp);
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
		if (tmp->word)
			free(tmp->word);
		free(tmp);
		tmp = NULL;
	}
}

void clean(t_exec *utils)
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
}

void	cleaning_parsing(t_expand *exp, t_quote *state)
{	
	free(exp);
	exp = NULL;
	free(state);
	state = NULL;
}

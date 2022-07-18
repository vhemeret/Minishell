/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 06:07:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 04:55:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	free_lst(t_token *token)
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
	return (0);
}

int	print_message(int error)
{
	if (error == 1)
		dprintf(2, "minishell: syntax error near unexpected token `newline'\n");
	else if (error == 2)
		dprintf(2, "minishell: syntax error near unexpected token '&'\n");
	else if (error == 3)
		dprintf(2, "minishell: syntax error near unexpected token '&&'\n");
	else if (error == 4)
		dprintf(2, "minishell: syntax error double quote not closed\n");
	else if (error == 5)
		dprintf(2, "minishell: syntax error single quote not closed\n");
	return (0);
}

int	print_message_and_cleaning(int error, t_token **lst)
{
	if (error == 1)
		dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	if (error == 2)
		dprintf(2, "minishell: syntax error near unexpected token `<'\n");
	if (error == 3)
		dprintf(2, "minishell: syntax error near unexpected token `>'\n");
	if (error == 4)
		dprintf(2, "minishell: syntax error near unexpected token `<<'\n");
	if (error == 5)
		dprintf(2, "minishell: syntax error near unexpected token `>>'\n");
	if (error == 6)
		dprintf(2, "minishell: syntax error near unexpected token `||'\n");
	if (error == 7)
		dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	return (free_lst(*lst));
}

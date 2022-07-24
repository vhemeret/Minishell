/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 06:07:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 23:39:30 by vahemere         ###   ########.fr       */
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
			ft_free(tmp->word);
		ft_free(tmp);
		tmp = NULL;
	}
	return (0);
}

int	print_message(int error)
{
	if (error == 1)
	{
		write(2, "minishell: syntax error near", 28);
		write(2, "unexpected token `newline'\n", 27);
	}
	else if (error == 2)
		write(2, "minishell: syntax error near unexpected token '&'\n", 50);
	else if (error == 3)
		write(2, "minishell: syntax error near unexpected token '&&'\n", 51);
	else if (error == 4)
		write(2, "minishell: syntax error double quote not closed\n", 48);
	else if (error == 5)
		write(2, "minishell: syntax error single quote not closed\n", 48);
	return (0);
}

int	print_message_and_cleaning(int error, t_token **lst)
{
	if (error == 1)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	if (error == 2)
		write(2, "minishell: syntax error near unexpected token `<'\n", 50);
	if (error == 3)
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
	if (error == 4)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
	if (error == 5)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
	if (error == 6)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	if (error == 7)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	return (free_lst(*lst));
}

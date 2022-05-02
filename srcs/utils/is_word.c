/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:28 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/02 00:29:17 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sp_word(char *cmd, int i, t_quote *state)
{
	if (!is_whitespace(cmd[i]) && (i == 0 || is_whitespace(cmd[i - 1])
		|| cmd[i - 1] == '|' || cmd[i - 1] == '<' || cmd[i - 1] == '>')
		&& state->is_quote == 0 && state->is_dquote == 0)
		{
			if (cmd[i] == '"' || cmd[i] == '\'')
				return (0);
			else
				return (1);
		}
	return (0);
}

int	pipe_word(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '|' && state->is_dquote == 0 && state->is_quote == 0)
		return (1);
	return (0);
}

int	redir_word(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '<' && (cmd[i + 1] != '<' || cmd[i + 1] == '<')
		&& state->is_quote == 0 && state->is_dquote == 0)
		return (1);
	else if (cmd[i] == '>' && (cmd[i + 1] != '>' || cmd[i + 1] == '>')
		&& state->is_quote == 0 && state->is_dquote == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:28 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/15 02:20:45 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	spr_word(char *cmd, int i)
// {
// 	if (!is_whitespace(cmd[i]) && (i == 0 || is_whitespace(cmd[i - 1])
// 		|| cmd[i - 1] == '|' || cmd[i - 1] == '<' || cmd[i - 1] == '>'))
// 				return (1);
// 	return (0);
// }

int	spr_word2(char *cmd, int i, t_quote *state)
{
	// printf("word -> %s, state -> d%i s%i\n", &cmd[i], state->is_dquote, state->is_quote);
	if (state->is_quote == 1 || state->is_dquote == 1)
	{
		if (cmd[i] == '"' && state->is_dquote == 1)
			if (i != 0)
				if (sep_word(cmd[i - 1]))
					return (1);
		if (cmd[i] == '\'' && state->is_quote == 1)
			if (i != 0)
				if (sep_word(cmd[i - 1]))
					return (1);
		if (i == 0)
			return (1);
		return (0);
	}
	if (!is_whitespace(cmd[i]) && cmd[i] != '"' && cmd[i] != '\'' && (i == 0 || is_whitespace(cmd[i - 1])
		|| cmd[i - 1] == '|' || cmd[i - 1] == '<' || cmd[i - 1] == '>'))
			return (1);
	return (0);
}

int	end_word(char *cmd, int i, t_quote *state)
{
	if (sep_word(cmd[i]) && state->is_dquote == 0 && state->is_quote == 0)
		return (1);
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
	if (cmd[i] == '<' && state->is_quote == 0 && state->is_dquote == 0)
		return (1);
	else if (cmd[i] == '>' && state->is_quote == 0 && state->is_dquote == 0)
		return (1);
	return (0);
}

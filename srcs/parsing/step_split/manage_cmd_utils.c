/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 06:12:23 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/15 13:00:06 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	sep_word(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}

static void	increment_redir_word(char *cmd_line, int *i)
{
	if (cmd_line[*i] == '<' && cmd_line[*i + 1] && cmd_line[*i + 1] == '<')
	{
		if (cmd_line[*i + 1] && cmd_line[*i + 1] == '<')
			(*i)++;
	}
	else if (cmd_line[*i] == '>'
		&& cmd_line[*i + 1] && cmd_line[*i + 1] == '>')
	{
		if (cmd_line[*i + 1] && cmd_line[*i + 1] == '>')
			(*i)++;
	}
}

static void	increment_quote_word(char *cmd_line, t_quote *state, int *i)
{
	if (cmd_line[*i] == '\'' && state->is_quote == 1)
		*i += next_squote(&cmd_line[*i]);
	else if (cmd_line[*i] == '"' && state->is_dquote == 1)
		*i += next_dquote(&cmd_line[*i]);
}

int	nb_words(char *cmd, t_quote *state)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (cmd[++i])
	{
		quoting_state(cmd[i], state);
		if (is_word(cmd, i, state) || pipe_word(cmd, i, state)
			|| redir_word(cmd, i, state))
		{
			if ((cmd[i] == '<' && cmd[i + 1] && cmd[i + 1] == '<')
				|| (cmd[i] == '>' && cmd[i + 1] && cmd[i + 1] == '>'))
				increment_redir_word(cmd, &i);
			else if ((cmd[i] == '\'' && state->is_quote == 1)
				|| (cmd[i] == '"' && state->is_dquote == 1))
			{
				increment_quote_word(cmd, state, &i);
				if (cmd[i] == '\0')
					return (words += 1);
			}
			words++;
		}
	}
	return (words);
}

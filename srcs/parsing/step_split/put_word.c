/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 06:07:18 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 06:10:36 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*put_redir_in_tab(char *cmd_line, int *i, char *words)
{
	int	k;

	k = 0;
	if (cmd_line[*i] == '<')
		while (cmd_line[*i] && cmd_line[*i] == '<' && k < 2)
			words[k++] = cmd_line[(*i)++];
	else if (cmd_line[*i] == '>')
		while (cmd_line[*i] && cmd_line[*i] == '>' && k < 2)
			words[k++] = cmd_line[(*i)++];
	words[k] = '\0';
	return (words);
}

char	*put_sqword_in_tab(char *cmd_line, int *i, t_quote *state, char *words)
{
	int	k;

	k = 0;
	words[k++] = cmd_line[(*i)++];
	while (cmd_line[*i] && cmd_line[*i] != '\'')
		words[k++] = cmd_line[(*i)++];
	if (cmd_line[(*i)] == '\0')
	{
		words[k] = '\0';
		return (words);
	}
	if (cmd_line[*i] && !sep_word(cmd_line[*i]))
	{
		while (cmd_line[*i] && !end_word(cmd_line, *i, state))
		{
			quoting_state(cmd_line[*i], state);
			words[k++] = cmd_line[(*i)++];
		}
	}
	words[k] = '\0';
	return (words);
}

char	*put_dqword_in_tab(char *cmd_line, int *i, t_quote *state, char *words)
{
	int	k;

	k = 0;
	words[k++] = cmd_line[(*i)++];
	while (cmd_line[*i] && cmd_line[*i] != '"')
		words[k++] = cmd_line[(*i)++];
	if (cmd_line[(*i)] == '\0')
	{
		words[k] = '\0';
		return (words);
	}
	if (cmd_line[*i] && !sep_word(cmd_line[*i]))
	{
		while (cmd_line[*i] && !end_word(cmd_line, *i, state))
		{
			quoting_state(cmd_line[*i], state);
			words[k++] = cmd_line[(*i)++];
		}
	}
	words[k] = '\0';
	return (words);
}

char	*put_word_in_tab(char *cmd_line, int *i, t_quote *state, char *words)
{
	int	k;

	k = 0;
	if (cmd_line[*i] && cmd_line[*i] == ' ')
		while (cmd_line[*i] == ' ')
			(*i)++;
	while (cmd_line[*i] && !end_word(cmd_line, *i, state))
	{
		quoting_state(cmd_line[*i], state);
		words[k++] = cmd_line[(*i)++];
	}
	words[k] = '\0';
	return (words);
}

char	*put_pipe_in_tab(char *cmd_line, int *i, char *words)
{
	int	k;

	k = 0;
	words[k++] = cmd_line[(*i)++];
	words[k] = '\0';
	return (words);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/24 19:07:01 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	sep_word(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}

int	nb_words(char *cmd_line, t_quote *state)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (cmd_line[++i])
	{
		quoting_state(cmd_line[i], state);
		if (is_word(cmd_line, i, state) || pipe_word(cmd_line, i, state)
			|| redir_word(cmd_line, i, state))
		{
			if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
			{
				if (cmd_line[i + 1] && cmd_line[i + 1] == '<')
					i++;
			}
			else if (cmd_line[i] == '>'
				&& cmd_line[i + 1] && cmd_line[i + 1] == '>')
			{
				if (cmd_line[i + 1] && cmd_line[i + 1] == '>')
					i++;
			}
			else if (cmd_line[i] == '\'' && state->is_quote == 1)
			{
				i += next_squote(&cmd_line[i]);
				if (cmd_line[i] == '\0')
					return (words += 1);
			}
			else if (cmd_line[i] == '"' && state->is_dquote == 1)
			{
				i += next_dquote(&cmd_line[i]);
				if (cmd_line[i] == '\0')
					return (words += 1);
			}
			words++;
		}
	}
	return (words);
}

static int	on_word(char *cmd_line, int i, t_quote	*state)
{
	quoting_state(cmd_line[i], state);
	if (is_word(cmd_line, i, state)
		|| pipe_word(cmd_line, i, state)
		|| redir_word(cmd_line, i, state))
		return (1);
	else
		return (0);
	return (0);
}

static char	*put_words_into_tabs(char *cmd_line, int *i, t_quote *state)
{
	char	*words;
	int		j;
	int		k;

	j = *i;
	if (cmd_line[*i] == '<')
		while (cmd_line[*i] && cmd_line[*i] == '<' && (*i - j) < 2)
			(*i)++;
	else if (cmd_line[*i] == '>')
		while (cmd_line[*i] && cmd_line[*i] == '>' && (*i - j) < 2)
			(*i)++;
	else if (cmd_line[*i] == '\'' && state->is_quote == 1)
		*i = next_squote_len(cmd_line, *i, state);
	else if (cmd_line[*i] == '"' && state->is_dquote == 1)
		*i = next_dquote_len(cmd_line, *i, state);
	else if (pipe_word(cmd_line, *i, state))
		(*i)++;
	else
	{
		while (cmd_line[*i] && !end_word(cmd_line, *i, state))
		{
			quoting_state(cmd_line[*i], state);
			(*i)++;
		}
	}
	words = malloc(sizeof(char) * ((*i - j) + 1));
	if (!words)
		return (NULL);
	state->is_dquote = 0;
	state->is_dquote = 0;
	*i = j;
	k = 0;
	quoting_state(cmd_line[*i], state);
	if (cmd_line[*i] == '<')
		while (cmd_line[*i] && cmd_line[*i] == '<' && k < 2)
			words[k++] = cmd_line[(*i)++];
	else if (cmd_line[*i] == '>')
		while (cmd_line[*i] && cmd_line[*i] == '>' && k < 2)
			words[k++] = cmd_line[(*i)++];
	else if (cmd_line[*i] == '\'' && state->is_quote == 1)
	{
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
	}
	else if (cmd_line[*i] == '"' && state->is_dquote == 1)
	{
		words[k++] = cmd_line[(*i)++];
		while (cmd_line[*i] && cmd_line[*i] != '"')
			words[k++] = cmd_line[(*i)++];
		if (cmd_line[(*i)] == '\0')
		{
			words[k] = '\0';
			return (words);
		}
		if (cmd_line[*i] && !sep_word(cmd_line[*i]))
			while (cmd_line[*i] && !end_word(cmd_line, *i, state))
			{
				quoting_state(cmd_line[*i], state);
				words[k++] = cmd_line[(*i)++];
			}
	}
	else if (cmd_line[*i] == '|')
		words[k++] = cmd_line[(*i)++];
	else
	{
		if (cmd_line[*i] && cmd_line[*i] == ' ')
			while (cmd_line[*i] == ' ')
				(*i)++;
		while (cmd_line[*i] && !end_word(cmd_line, *i, state))
		{
			quoting_state(cmd_line[*i], state);
			words[k++] = cmd_line[(*i)++];
		}
	}
	words[k] = '\0';
	return (words);
}

t_token	*manage_cmd(char *cmd_line, char **env)
{
	t_quote	*state;
	t_token	*lst;
	char	**words;
	int		tab_index;
	int		i;

	tab_index = 0;
	if (!first_check(cmd_line))
		return (NULL);
	state = malloc(sizeof(t_quote));
	if (!state)
		return (NULL);
	if (!check_quote(cmd_line, state))
		return (NULL);
	words = malloc(sizeof(char *) * (nb_words(cmd_line, state) + 1));
	if (!words)
		return (NULL);
	state->is_dquote = 0;
	state->is_quote = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (on_word(cmd_line, i, state))
			words[tab_index++] = put_words_into_tabs(cmd_line, &i, state);
		else
			i++;
	}
	words[tab_index] = NULL;
	tokenizer(words, &lst, nb_words(cmd_line, state));
	if (!syntax_check(&lst))
		return (NULL);
	expand(&lst, state, env);
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/25 11:44:10 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_sep(char c)
{
	if (((c >= 9 && c <= 13) || c == ' ')
		|| c == '"' || c == '\'' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	nb_words(char *cmd_line, t_quote *state)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (cmd_line[++i])
	{
		quoting_state(cmd_line[i], state);
		if (sp_word(cmd_line, i, state) || pipe_word(cmd_line, i, state)
			|| redir_word(cmd_line, i, state)
			|| (cmd_line[i] == '"' && state->is_dquote == 1)
			|| (cmd_line[i] == '\'' && state->is_quote == 1))
		{
			if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '<')
					i++;
			else if (cmd_line[i] == '>' && cmd_line[i + 1] && cmd_line[i + 1] == '>')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '>')
					i++;
			else if (cmd_line[i] == '\'' && state->is_quote == 1)
				i += next_squote(&cmd_line[i]);
			else if (cmd_line[i] == '"' && state->is_dquote == 1)
				i += next_dquote(&cmd_line[i]);
			words++;
		}
	}
	return (words);
}

static int	is_word(char *cmd_line, t_quote	*state)
{
	int	i;

	i = -1;
	while (cmd_line[++i])
	{
		quoting_state(cmd_line[i], state);
		if (sp_word(cmd_line, i, state) || pipe_word(cmd_line, i, state)
			|| redir_word(cmd_line, i, state)
			|| (cmd_line[i] == '"' && state->is_dquote == 1)
			|| (cmd_line[i] == '\'' && state->is_quote == 1))
			return (1);
		else
			return (0);
	}
	return (0);
}

static char	*put_words_into_tabs(char *cmd_line, t_quote *state)
{
	char *words;
	int	i;

	i = 0;
	if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
		while (cmd_line[i + 1] && cmd_line[i + 1] == '<')
			i++;
	else if (cmd_line[i] == '>' && cmd_line[i + 1] && cmd_line[i + 1] == '>')
		while (cmd_line[i + 1] && cmd_line[i + 1] == '>')
			i++;
	else if (cmd_line[i] == '\'' && state->is_quote == 1)
		i = next_squote_len(&cmd_line[i]);
	else if (cmd_line[i] == '"' && state->is_dquote == 1)
		i = next_dquote_len(&cmd_line[i]);
	else
		while (cmd_line[i] && !is_sep(cmd_line[i]))
			i++;
	words = malloc(sizeof(char) * (i + 1));
	if (!words)
		return (NULL);
	printf("len word -> %i\n", i);
	i = 0;
	if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
	{
		while (cmd_line[i + 1] && cmd_line[i + 1] == '<')
		{
			words[i] = cmd_line[i];
			i++;
		}
	}
	else if (cmd_line[i] == '>' && cmd_line[i + 1] && cmd_line[i + 1] == '>')
	{
		while (cmd_line[i + 1] && cmd_line[i + 1] == '>')
		{
			words[i] = cmd_line[i];
			i++;
		}
	}
	else if (cmd_line[i] == '\'' && state->is_quote == 1)
	{
		while (cmd_line[i] && cmd_line[i] != '\'')
		{
			words[i] = cmd_line[i];
			i++;
		}
	}
	else if (cmd_line[i] == '"' && state->is_dquote == 1)
	{
		while (cmd_line[i] && cmd_line[i] != '"')
		{
			words[i] = cmd_line[i];
			i++;
		}
	}
	else
	{
		while (cmd_line[i] && !is_sep(cmd_line[i]))
		{
			words[i] = cmd_line[i];
			i++;
		}
	}
	words[i] = '\0';
	return (words);
}

void	manage_cmd(char *cmd_line)
{
	t_quote	*state;
	char	**words;
	int		tab_index;
	int		len;
	int		i;

	tab_index = 0;
	state = malloc(sizeof(t_quote));
	if (!state)
		return ;
	state->is_dquote = 0;
	state->is_quote = 0;
	len = nb_words(cmd_line, state);
	words = malloc(sizeof(char *) * (len + 1));
	if (!words)
		return ;
	printf("nb words:\t%i\n", len);
	state->is_dquote = 0;
	state->is_quote = 0;
	i = -1;
	while (cmd_line[++i])
	{
		printf("%c\n", cmd_line[i]);
		if (is_word(&cmd_line[i], state))
		{
			printf("ici\n");
			words[tab_index] = put_words_into_tabs(&cmd_line[i], state);
			tab_index++;
		}
	}
	words[tab_index] = NULL;
	i = -1;
	while (words[++i])
		printf("tab[%i]\t=\t%s\n", i, words[i]);
}

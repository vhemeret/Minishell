/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/03 03:26:34 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_sep(char c)
{
	if (c == '"' || c == '\'' || c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}

// calcul nombre de mot pour le double tab
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

// retourne 1 si l' on est bien sur un mot
static int	is_word(char *cmd_line, int i, t_quote	*state)
{
	quoting_state(cmd_line[i], state);
	if (sp_word(cmd_line, i, state) || pipe_word(cmd_line, i, state)
		|| redir_word(cmd_line, i, state)
		|| (cmd_line[i] == '"' && state->is_dquote == 1)
		|| (cmd_line[i] == '\'' && state->is_quote == 1))
		return (1);
	else
		return (0);
	return (0);
}

// aloue la taille d'un mot pour par la suite le mettre dans le double tableau
static char	*put_words_into_tabs(char *cmd_line, int i, t_quote *state)
{
	char	*words;
	int		j;
	int		k;

	j = i;
	if (cmd_line[i] == '<')
		while (cmd_line[i] && cmd_line[i] == '<')
			i++;
	else if (cmd_line[i] == '>')
		while (cmd_line[i] && cmd_line[i] == '>')
			i++;
	else if (cmd_line[i] == '\'' && state->is_quote == 1)
		i = next_squote_len(cmd_line, i);
	else if (cmd_line[i] == '"' && state->is_dquote == 1)
		i = next_dquote_len(cmd_line, i);
	else if (pipe_word(cmd_line, i, state))
		i++;
	else
		while (cmd_line[i] && !is_sep(cmd_line[i]))
			i++;
	words = malloc(sizeof(char) * ((i - j) + 1));
	if (!words)
		return (NULL);
	i = j;
	k = 0;
	if (cmd_line[i] == '<')
		while (cmd_line[i] && cmd_line[i] == '<')
			words[k++] = cmd_line[i++];
	else if (cmd_line[i] == '>')
		while (cmd_line[i] && cmd_line[i] == '>')
			words[k++] = cmd_line[i++];
	else if (cmd_line[i] == '\'' && state->is_quote == 1)
	{
		i++;
		while (cmd_line[i] && cmd_line[i] != '\'')
			words[k++] = cmd_line[i++];
		if (cmd_line[i + 1] && !is_sep(cmd_line[i + 1]))
		{
			i++;
			while (cmd_line[i] && !is_sep(cmd_line[i]))
				words[k++] = cmd_line[i++];
		}
	}
	else if (cmd_line[i] == '"' && state->is_dquote == 1)
	{
		words[k++] = cmd_line[i++];
		while (cmd_line[i] && cmd_line[i] != '"')
			words[k++] = cmd_line[i++];
		words[k++] = cmd_line[i++];
		if (cmd_line[i] && !is_sep(cmd_line[i]))
			while (cmd_line[i] && !is_sep(cmd_line[i]))
				words[k++] = cmd_line[i++];
	}
	else if (cmd_line[i] == '|')
		words[k++] = cmd_line[i];
	else
	{
		if (cmd_line[i] && cmd_line[i] == ' ')
			while (cmd_line[i] == ' ')
				i++;
		while (cmd_line[i] && !is_sep(cmd_line[i]))
			words[k++] = cmd_line[i++];
	}
	words[k] = '\0';
	return (words);
}

// aloue le double tableau et place chaque mot alouer avec la fonction ci dessus dedans.
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
	state->is_dquote = 0;
	state->is_quote = 0;
	i = 0;
	while (tab_index < len)
	{
		if (is_word(cmd_line, i, state))
		{
			words[tab_index] = put_words_into_tabs(cmd_line, i, state);
			if (cmd_line[i] == '<')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '<')
					i++;
			if (cmd_line[i] == '>')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '>')
					i++;
			tab_index++;
		}
		i++;
	}
	words[tab_index] = NULL;
	// PRINT
	// i = -1;
	// while (words[++i])
	// 	printf("tab[%i]\t=\t%s\n", i, words[i]);
	tokenizer(words);
}

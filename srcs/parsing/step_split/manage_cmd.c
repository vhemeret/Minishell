/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/15 05:01:20 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	sep_word(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}

// int	is_sep(char c)
// {
// 	if (c == '"' || c == '\'' || c == '<' || c == '>' || c == '|' || c == ' ')
// 		return (1);
// 	return (0);
// }

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
		if (spr_word2(cmd_line, i, state) || pipe_word(cmd_line, i, state)
			|| redir_word(cmd_line, i, state))
		{
			if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
			{
				if (cmd_line[i + 1] && cmd_line[i + 1] == '<')
					i++;
			}
			else if (cmd_line[i] == '>' && cmd_line[i + 1] && cmd_line[i + 1] == '>')
			{
				if (cmd_line[i + 1] && cmd_line[i + 1] == '>')
					i++;
			}
			else if (cmd_line[i] == '\'' && state->is_quote == 1)
				i += next_squote(&cmd_line[i]);
			else if (cmd_line[i] == '"' && state->is_dquote == 1)
				i += next_dquote(&cmd_line[i]);
			words++;
		}
	}
	printf("\t\033[34;01mNB_WORDS -> %i\033[00m\n\t----------\n\n", words);
	return (words);
}

// retourne 1 si l' on est bien sur un mot
static int	is_word(char *cmd_line, int i, t_quote	*state)
{
	quoting_state(cmd_line[i], state);
	if (spr_word2(cmd_line, i, state)
		|| pipe_word(cmd_line, i, state)
		|| redir_word(cmd_line, i, state))
	{
		printf("caractere : %s\n", &cmd_line[i]);
		return (1);
	}
	else
		return (0);
	return (0);
}

// aloue la taille d'un mot pour par la suite le mettre dans le double tableau
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
	printf("len words %i\n", (*i - j));
	words = malloc(sizeof(char) * ((*i - j) + 1));
	if (!words)
		return (NULL);
	state->is_dquote = 0;
	state->is_dquote = 0;
	*i = j;
	k = 0;
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
		words[k++] = cmd_line[(*i)++];
		if (cmd_line[*i] && !sep_word(cmd_line[*i]))
			while (cmd_line[*i] && !end_word(cmd_line, *i, state))
			{
				quoting_state(cmd_line[*i], state);
				words[k++] = cmd_line[(*i)++];
			}
	}
	else if (cmd_line[*i] == '"' && state->is_dquote == 1)
	{
		words[k++] = cmd_line[(*i)++];
		while (cmd_line[*i] && cmd_line[*i] != '"')
			words[k++] = cmd_line[(*i)++];
		words[k++] = cmd_line[(*i)++];
		if (cmd_line[*i] && !sep_word(cmd_line[*i]))
			while (cmd_line[*i] && !end_word(cmd_line, *i, state))
			{
				quoting_state(cmd_line[*i], state);
				words[k++] = cmd_line[(*i)++];
			}
	}
	else if (cmd_line[*i] == '|')
		words[k++] = cmd_line[*i];
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
	i = 0;
	while (tab_index < len)
	{
		if (is_word(cmd_line, i, state))
		{
			printf("\033[33;01mword found -> [%s]\t\t dq [%i] sq [%i]\033[00m\n", &cmd_line[i], state->is_dquote, state->is_quote);
			words[tab_index] = put_words_into_tabs(cmd_line, &i, state);
			printf("\033[32;01mword remaining -> [%s]\t\t dq [%i] sq [%i]\033[00m\n", &cmd_line[i], state->is_dquote, state->is_quote);
			tab_index++;
		}
		i++;
	}
	words[tab_index] = NULL;
	printf("\n\n");
	tokenizer(words);
}

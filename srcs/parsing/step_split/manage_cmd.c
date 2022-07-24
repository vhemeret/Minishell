/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 23:39:30 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

void	len_malloc_word(char *cmd_line, int *i, t_quote *state)
{
	int		j;

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
}

static char	*put_in_tab(char *cmd_line, int *i, t_quote *state)
{
	char	*words;
	int		j;

	j = *i;
	len_malloc_word(cmd_line, i, state);
	words = ft_malloc(sizeof(char) * ((*i - j) + 1));
	if (!words)
		return (NULL);
	state->is_dquote = 0;
	state->is_dquote = 0;
	*i = j;
	quoting_state(cmd_line[*i], state);
	if (cmd_line[*i] == '<' || cmd_line[*i] == '>')
		return (put_redir_in_tab(cmd_line, i, words));
	else if (cmd_line[*i] == '\'' && state->is_quote == 1)
		return (put_sqword_in_tab(cmd_line, i, state, words));
	else if (cmd_line[*i] == '"' && state->is_dquote == 1)
		return (put_dqword_in_tab(cmd_line, i, state, words));
	else if (cmd_line[*i] == '|')
		return (put_pipe_in_tab(cmd_line, i, words));
	else
		return (put_word_in_tab(cmd_line, i, state, words));
	return (NULL);
}

char	**get_array_with_words(char *cmd_line, char **arr, t_quote *state)
{
	int	i;
	int	tab_index;

	i = 0;
	tab_index = 0;
	while (cmd_line[i])
	{
		if (on_word(cmd_line, i, state))
			arr[tab_index++] = put_in_tab(cmd_line, &i, state);
		else
			i++;
	}
	arr[tab_index] = NULL;
	return (arr);
}

t_token	*manage_cmd(char *cmd_line, char **env)
{
	t_quote	*state;
	t_token	*lst;
	char	**arr;

	if (!first_check(cmd_line))
		return (NULL);
	state = ft_malloc(sizeof(t_quote));
	if (!state)
		return (NULL);
	if (!check_quote(cmd_line, state))
		return (NULL);
	arr = ft_malloc(sizeof(char *) * (nb_words(cmd_line, state) + 1));
	if (!arr)
		return (NULL);
	state->is_dquote = 0;
	state->is_quote = 0;
	arr = get_array_with_words(cmd_line, arr, state);
	tokenizer(arr, &lst, nb_words(cmd_line, state));
	if (!syntax_check(&lst))
	{
		ft_free(state);
		return (NULL);
	}
	expand(&lst, state, env);
	return (lst);
}

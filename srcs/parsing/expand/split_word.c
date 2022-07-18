/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:49:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 02:50:40 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	on_word(char *word, int index, t_quote *state)
{
	if (word[index] != ' ' && (index == 0 || word[index - 1] == ' '))
	{
		if ((word[index] == '"' && state->is_dquote == 0)
			|| (word[index] == '\'' && state->is_dquote == 0))
		{
			if (word[index + 1])
				if (word[index + 1] != ' ')
					return (1);
		}
		else
			return (1);
	}
	return (0);
}

char	*copy_word(char *word, t_quote *state, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (word[i] && word[i] != ' ')
	{
		if ((word[i] == '"' && state->is_quote == 0)
			|| (word[i] == '\'' && state->is_dquote == 0))
			i++;
		else
		{
			str[j++] = word[i];
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*malloc_word(char *word, t_quote *state)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (word[i] && word[i] != ' ')
	{
		if ((word[i] == '"' && state->is_quote == 0)
			|| (word[i] == '\'' && state->is_dquote == 0))
			i++;
		else
		{
			i++;
			j++;
		}
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	return (copy_word(word, state, str));
}

int	len_d_array(char *word, t_quote *state)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	state->is_dquote = 0;
	state->is_quote = 0;
	while (word[++i])
	{
		quoting_state(word[i], state);
		if (on_word(word, i, state))
			j++;
	}
	return (j);
}

char	**split_word(char *word, t_quote *state)
{
	int		i;
	int		j;
	char	**arr;

	arr = malloc(sizeof(char *) * (len_d_array(word, state) + 1));
	if (!arr)
		return (NULL);
	i = -1;
	j = 0;
	state->is_dquote = 0;
	state->is_quote = 0;
	while (word[++i])
	{
		quoting_state(word[i], state);
		if (on_word(word, i, state))
			arr[j++] = malloc_word(&word[i], state);
	}
	arr[j] = NULL;
	return (arr);
}

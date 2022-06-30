/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:52:39 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/30 04:02:48 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*malloc_word_without_quote(char *old, char *nw, t_quote *state)
{
	int	i;
	int	j;
	
	i = -1;
	j = 0;
	state->is_quote = 0;
	state->is_dquote = 0;
	while (old[++i])
	{
		if (old[i] == '"' && state->is_quote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		if (old[i] == '\'' && state->is_dquote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		nw[j++] = old[i];
	}
	nw[j] = '\0';
	free(old);
	old = NULL;
	return (nw);
}

char	*word_without_quote(char *old, t_quote *state)
{
	char	*nw;
	int		i;
	int		len;

	i = -1;
	state->is_quote = 0;
	state->is_dquote = 0;
	while (old[++i])
	{
		quoting_state(old[i], state);
		if (old[i] == '"' && state->is_quote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		if (old[i] == '\'' && state->is_dquote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		len++;
	}
	nw = malloc(sizeof(char) * (len + 1));
	return (malloc_word_without_quote(old, nw, state));
}

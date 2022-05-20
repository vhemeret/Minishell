/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:55:45 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/20 09:48:55 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	next_squote(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\'' && cmd[i + 1] == '\'')
		return (i);
	else if (cmd[i] == '\'')
		i++;
	while (cmd[i] && cmd[i + 1] != '\'')
		i++;
	return (i);
}

int	next_dquote(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '"' && cmd[i + 1] == '"')
		return (i);
	else if (cmd[i] == '"')
		i++;
	while (cmd[i] && cmd[i + 1] != '"')
		i++;
	return (i);
}

int	next_squote_len(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '\'')
		i++;
	while (cmd[i] && cmd[i] != '\'')
		i++;
	if (cmd[i] == '\0')
		return (i);
	quoting_state(cmd[i], state);
	i++;
	if (cmd[i] && !sep_word(cmd[i]))
	{
		while (cmd[i] && !end_word(cmd, i, state))
		{
			quoting_state(cmd[i], state);
			i++;
		}
	}
	return (i);
}

int	next_dquote_len(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '"')
		i++;
	while (cmd[i] && cmd[i] != '"')
		i++;
	if (cmd[i] == '\0')
		return (i);
	quoting_state(cmd[i], state);
	i++;
	if (cmd[i] && !sep_word(cmd[i]))
	{
		while (cmd[i] && !end_word(cmd, i, state))
		{
			quoting_state(cmd[i], state);
			i++;
		}
	}
	return (i);
}

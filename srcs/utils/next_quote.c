/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:55:45 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/02 02:48:17 by vahemere         ###   ########.fr       */
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

int	next_squote_len(char *cmd, int i)
{
	if (cmd[i] == '\'')
		i++;
	while (cmd[i + 1] && cmd[i + 1] != '\'')
		i++;
	return (i);
}

int	next_dquote_len(char *cmd, int i)
{
	if (cmd[i] == '"')
		i++;
	while (cmd[i + 1] && cmd[i + 1] != '"')
		i++;
	return (i);
}

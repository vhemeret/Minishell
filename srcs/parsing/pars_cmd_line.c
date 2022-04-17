/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:12:49 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/17 23:09:12 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	pars_pipe(char *cmd_line)
{
	int	i;

	i = 0;
	if (is_whitespace(cmd_line[0]))
		while (cmd_line[i] && is_whitespace(cmd_line[i]))
			i++;
	if (cmd_line[i] == '|')
		return (0);
	while (cmd_line[i + 1])
		i++;
	if (is_whitespace(cmd_line[i]))
		while (cmd_line[i] && is_whitespace(cmd_line[i]))
			i--;
	if (cmd_line[i] == '|')
		return (0);
	return (1);
}

static int	pars_quote(char *cmd_line)
{
	int	quote;
	int	dquote;
	int	i;
	
	i = -1;
	quote = 0;
	dquote = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '"')
			dquote++;
		else if (cmd_line[i] == '\'')
			quote++;
	}
	if (quote % 2 != 0)
	{
		printf("minishell:	syntax error single quote not closed\n");
		return (0);
	}
	if (dquote % 2 != 0)
	{
		printf("minishell:	syntax error double quote not closed\n");
		return (0);
	}
	return (1);
}

int	pars_cmd_line(char *cmd_line)
{
	if (!pars_quote(cmd_line))
		return (0);
	if (!pars_pipe(cmd_line))
	{
		printf("minishell:	syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

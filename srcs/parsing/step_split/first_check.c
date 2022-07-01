/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:20:48 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 02:50:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	first_check(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
	{
		if (cmd[i + 1] == '\0')
		{
			dprintf(2, "minishell: syntax error near unexpected token `newline'\n ");
			return (0);
		}
		else
		{
			if ((cmd[i] == '<' && (cmd[i + 1] == '<' || cmd[i + 1] == '>'))
				|| (cmd[i] == '>' && cmd[i + 1] == '>'))
			{
				if (cmd[i + 2] == '\0')
				{
					dprintf(2, "minishell: syntax error near unexpected token `newline'\n ");
					return (0);
				}
			}
		}
	}
	if (cmd[i] && cmd [i] == '&')
	{
		if (cmd[i + 1] == '\0')
		{
			dprintf(2, "minishell:	syntax error near unexpected token '&'\n ");
			return (0);
		}
		while (cmd[i] && cmd[i] == '&')
			i++;
		if (cmd[i] == '\0')
		{
			dprintf(2, "minishell:	syntax error near unexpected token '&&'\n ");
			return (0);
		}
	}
	if ((cmd[i] == '!' || cmd[i] == ':') && cmd[1] == '\0')
		return (0);
	else if (cmd[i] == ' ' || cmd[i] == '\t')
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}

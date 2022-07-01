/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:11:46 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 02:49:40 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_quote(char *cmd_line, t_quote *state)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	state->is_quote = 0;
	state->is_dquote = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '\'' && state->is_dquote == 0)
		{
			quoting_state(cmd_line[i], state);
			j++;
		}
		else if (cmd_line[i] == '"' && state->is_quote == 0)
		{
			quoting_state(cmd_line[i], state);
			k++;
		}
	}
	if (j % 2 != 0)
	{
		dprintf(2, "minishell:	syntax error single quote not closed\n");
		return (0);
	}
	if (k % 2 != 0)
	{
		dprintf(2, "minishell:	syntax error double quote not closed\n");
		return (0);
	}
	state->is_quote = 0;
	state->is_dquote = 0;
	return (1);
}

int	syntax_check(t_token **lst)
{
	t_token	*tmp;
	t_token	*save;

	tmp = (*lst);
	save = tmp;
	tmp = tmp->next;
	if (tmp)
	{
		if (save->type == PIPE && tmp->type == PIPE)
			return (print_and_free("minishell:	syntax error near unexpected token `||'", lst));
	}
	if (save->type == PIPE && (!save->next || !save->back))
		return (print_and_free("minishell:	syntax error near unexpected token `|'", lst));
	while (tmp)
	{
		if (save->type == R_IN || save->type == R_OUT || save->type == DR_IN || save->type == DR_OUT)
		{
			if (tmp->type == PIPE)
				return (print_and_free("minishell:	syntax error near unexpected token `|'", lst));
			else if (tmp->type == R_IN)
				return (print_and_free("minishell:	syntax error near unexpected token `<'", lst));
			else if (tmp->type == R_OUT)
				return (print_and_free("minishell:	syntax error near unexpected token `>'", lst));
			else if (tmp->type == DR_IN)
				return (print_and_free("minishell:	syntax error near unexpected token `>>'", lst));
			else if (tmp->type == DR_OUT)
				return (print_and_free("minishell:	syntax error near unexpected token `<<'", lst));
		}
		save = tmp;
		tmp = tmp->next;
	}
	return (1);
}

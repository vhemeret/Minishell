/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:11:46 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 04:46:58 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	quote_error(int j, int k, t_quote *state)
{
	if (j % 2 != 0)
		return (print_message(5));
	if (k % 2 != 0)
		return (print_message(4));
	state->is_quote = 0;
	state->is_dquote = 0;
	return (1);
}

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
	return (quote_error(j, k, state));
}

int	check_after_redir(t_token *tmp, t_token **lst)
{
	if (tmp->type == PIPE)
		return (print_message_and_cleaning(1, lst));
	else if (tmp->type == R_IN)
		return (print_message_and_cleaning(2, lst));
	else if (tmp->type == R_OUT)
		return (print_message_and_cleaning(3, lst));
	else if (tmp->type == DR_IN)
		return (print_message_and_cleaning(4, lst));
	else if (tmp->type == DR_OUT)
		return (print_message_and_cleaning(5, lst));
	return (0);
}

int	find_syntax_error(t_token *tmp, t_token *save)
{
	if (save->type == PIPE && tmp->type == PIPE)
		return (1);
	else if (save->type == R_IN || save->type == R_OUT
		|| save->type == DR_IN || save->type == DR_OUT)
	{
		if (tmp->type == PIPE || tmp->type == R_IN || tmp->type == R_OUT
			|| tmp->type == DR_IN || tmp->type == DR_OUT)
			return (1);
	}
	return (0);
}

int	syntax_check(t_token **lst)
{
	t_token	*tmp;
	t_token	*save;

	tmp = (*lst);
	save = tmp;
	tmp = tmp->next;
	if (tmp)
		if (save->type == PIPE && tmp->type == PIPE)
			return (print_message_and_cleaning(6, lst));
	if (save->type == PIPE && (!save->next || !save->back))
		return (print_message_and_cleaning(7, lst));
	while (tmp)
	{
		if (find_syntax_error(tmp, save))
			return (check_after_redir(tmp, lst));
		if (!tmp->next && tmp->type == PIPE)
			return (print_message_and_cleaning(7, lst));
		save = tmp;
		tmp = tmp->next;
	}
	return (1);
}

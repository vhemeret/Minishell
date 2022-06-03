/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:11:46 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/20 13:32:50 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_quote(char *cmd_line, t_quote *state)
{
	int i;
	int j;
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


int syntax_check(t_token **lst)
{
	t_token *tmp;
	t_token *save;
	
	tmp = (*lst);
	save = tmp;
	tmp = tmp->next;
	if (save->word[0] == '|')
		return (print_and_free("minishell:	syntax error near unexpected token `|'\n", lst));	
	while (tmp)
	{
		if (save->type == 2 || save->type == 3 || save->type == 5 || save->type == 4)
		{
				if (tmp->type == 10)
					return (print_and_free("minishell:	syntax error near unexpected token `|'\n", lst));
				else if (tmp->type == 2)
					return (print_and_free("minishell:	syntax error near unexpected token `<'\n", lst));
				else if (tmp->type == 3)
					return (print_and_free("minishell:	syntax error near unexpected token `>'\n", lst));
				else if (tmp->type == 4)
					return (print_and_free("minishell:	syntax error near unexpected token `>>'\n", lst));
				else if (tmp->type == 5)
					return (print_and_free("minishell:	syntax error near unexpected token `<<'\n", lst));
		}
		save = tmp;
		tmp = tmp->next;
	}
	if (save->word[0] == '|')
		return (print_and_free("minishell:	syntax error near unexpected token `|'\n", lst));	
	return (1);
}

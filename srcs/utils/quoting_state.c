/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:29:57 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/20 14:13:04 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quoting_state(char c, t_quote *state)
{
	if (c == '\'')
	{
		if (state->is_quote == 0)
			state->is_quote = 1;
		else
			state->is_quote = 0;
	}
	else if (c == '"')
	{
		if (state->is_dquote == 0)
			state->is_dquote = 1;
		else
			state->is_dquote = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/06 18:36:24 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **malloc_darrgs(char *cmd)
{
	int	i;
	int	word;
	
	i = -1;
	word = 0;
	while (cmd[++i] && cmd[i] != '|')
	{
		
	}
}

char	**get_cmd(char *cmd)
{
	int		i;
	char	**cmd;
	t_data	data;

	i = -1;
	data.is_quote = 0;
	data.is_dquote = 0;
	cmd = malloc_darrgs(cmd);
	while (cmd[++i] && cmd[i] != '|')
	{
		
	}
}
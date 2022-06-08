/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:04:55 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/08 17:39:33 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int		get_nb_arg(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

char	**get_arg(t_token *token)
{
	char	**arg;
	int		nb_arg;
	int		i;

	i = 0;
	nb_arg = get_nb_arg(token);
	//printf("nb_arg = %i\n", nb_arg);
	arg = malloc(sizeof(char *) * (nb_arg + 1));
	*arg = token->word;
	token = token->next;
	//printf("arg 0 = %s\n", arg[0]);
	while (++i < nb_arg && token->type == ARG)
	{
		arg[i] = token->word;
		//printf("arg %i = %s\n",i, arg[i]);
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	set_r_in(t_exec	*utils, t_token *token)
{
	if (utils->in != -2)
		utils->in = -2;
	while (token && token->type != R_IN && token->type != PIPE)
		token = token->next;
	if (token && token->type == R_IN && token->next->type == INFILE)
	{
		if (!access(token->next->word, F_OK))
			utils->in = open(token->next->word, O_RDONLY);
		else
			utils->in = -1;
	}
}

void	set_r_out(t_exec	*utils, t_token *token)
{

	if (utils->out != -2)
		utils->out = -2;
	while (token && token->type != R_OUT && token->type != PIPE)
		token = token->next;
	if (token && token->type == R_OUT && token->next->type == OUTFILE)
	{
		utils->out = open(token->next->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (utils->out == -1)
			perror("Outfile :");
	}
}

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
	}
	return (path);
}
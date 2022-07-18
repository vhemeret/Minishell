/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 04:07:32 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ctrl_c(int test)
{
	(void)(test);
	rl_redisplay();
	printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*ret;
	(void)	av;
	t_token	*token;
	t_exec	*utils;

	utils = NULL;
	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	signal(SIGINT, &ctrl_c);
	while (1)
	{
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		if (ft_strlen(ret) != 0)
		{
			token = manage_cmd(ret, envp);
			if (ret && *ret)
				add_history(ret);
			free(ret);
			if (!utils)
				utils = init_exec(token, envp);
			// else
			// 	refresh(token, utils);
			// if (utils)
			// {
			// 	exec(token, utils);
			// 	clean(utils);
			// }
			t_token *tmp;

			/*########### PRINT ###########*/
			tmp = token;
			char	*types[9] = {"CMD", "ARG", "R_IN", "R_OUT", "DR_IN", "DR_OUT", "FD", "LIMITOR", "PIPE"};
			while (tmp)
			{
				printf("\033[31;01m\t[%s]\033[00m \033[32;01m|\033[00m \033[33;01m[%s]\033[00m\n", tmp->word, types[tmp->type]);
				tmp = tmp->next;
			}
			/*#############################*/
			if (utils)
			{
				exec(token, utils);
				clean(utils);
			}
			break ;
		}
	}
	return (0);
}

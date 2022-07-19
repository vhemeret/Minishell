/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 23:45:08 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ctrl_c(int test)
{
	(void)(test);
	printf("\n");
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sig()
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char	*ret;
	(void)	av;
	t_token	*token;
	t_exec	*utils;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	utils = init_exec(NULL, envp);
	handle_sig();
	while (1)
	{
		
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		if (!ret)
		{
			printf("exit\n");
			exit(0);
		}
		else if (ft_strlen(ret) != 0)
		{
			token = manage_cmd(ret, utils->envp);
			if (ret && *ret)
				add_history(ret);
			free(ret);
			refresh(token, utils);
			if (utils)
			{
				exec(token, utils);
				clean(utils);
			}
		}
	}
	return (0);
}

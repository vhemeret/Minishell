/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 20:05:14 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_all	g_all;

void	launch_process(char *ret)
{
	t_token	*token;

	token = manage_cmd(ret, g_all.utils->envp);
	if (ret && *ret)
		add_history(ret);
	ft_free(ret);
	refresh(token, g_all.utils);
	if (g_all.utils && g_all.utils->can_run == 1)
		exec(token);
	clean(g_all.utils);
}

int	main(int ac, char **av, char **envp)
{
	char	*ret;

	(void)av;
	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	g_all.utils = init_exec(envp);
	while (1)
	{
		handle_sig();
		ret = readline("\001\033[0;35m\002minishell\001\033[0;32m ✗\033[0m\002 ");
		if (!ret)
		{
			printf("exit\n");
			ft_free_all();
			exit(0);
		}
		else if (ft_strlen(ret) != 0)
			launch_process(ret);
	}
	return (0);
}

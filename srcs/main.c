/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/20 00:53:45 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_cmd_test(t_cmd *cmd)
// {
// 	while(cmd)
// 	{
// 		printf("%s\n", cmd->cmd);
// 		cmd = cmd->next;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	char	*ret;
	(void)	av;
	(void)	env;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	while (1)
	{
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		if (ft_strlen(ret) != 0)
		{
			if (!pars_cmd_line(ret))
				continue;
			manage_cmd(ret);
			if (ret && *ret)
				add_history(ret);
				// return (0);
				//print_cmd_test(cmd);
			free(ret);
		}
	}
	return (0);
}
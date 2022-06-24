/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/24 18:29:20 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*ret;
	(void)	av;
	t_token	*token;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	while (1)
	{
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		//printf("%s\n", ret);
		if (ft_strlen(ret) != 0)
		{
			token = manage_cmd(ret, envp);
			//(void)	token;
			if (ret && *ret)
				add_history(ret);
			//cd(ret);
			free(ret);
			exec(token, env);
		}
	}
	return (0);
}

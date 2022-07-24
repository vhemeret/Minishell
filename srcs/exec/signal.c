/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:01:42 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 19:40:59 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_all(void)
{
	g_all.g_mem = NULL;
}

void	ctrl_c(int test)
{
	(void)test;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c_here(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	close(0);
	g_all.utils->can_run = 0;
	g_all.utils->on_here_doc = 0;
	g_all.utils->err = 130;
}

void	handle_sig(void)
{
	if (g_all.utils->on_here_doc == 1)
		signal(SIGINT, &ctrl_c_here);
	else
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}

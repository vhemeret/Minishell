/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:05:59 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 19:43:02 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_mem(void *addr)
{
	t_mem	*new_mem;
	t_mem	*tmp;

	new_mem = malloc(sizeof(t_mem));
	new_mem->addr = addr;
	new_mem->next = NULL;
	if (g_all.g_mem == NULL)
		g_all.g_mem = new_mem;
	else
	{
		tmp = g_all.g_mem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_mem;
	}
}

void	*ft_malloc(size_t size)
{
	void	*addr;

	addr = malloc(size);
	add_mem(addr);
	return (addr);
}

void	ft_free(void *addr)
{
	t_mem	*tmp;
	t_mem	*ex;
	t_mem	*next;

	tmp = g_all.g_mem;
	ex = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->addr == addr)
		{
			free(tmp->addr);
			free(tmp);
			if (ex)
				ex->next = next;
			else
				g_all.g_mem = next;
			return ;
		}
		ex = tmp;
		tmp = tmp->next;
	}
}

void	ft_free_all(void)
{
	t_mem	*tmp;
	t_mem	*next;

	tmp = g_all.g_mem;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->addr);
		free(tmp);
		tmp = next;
	}
}

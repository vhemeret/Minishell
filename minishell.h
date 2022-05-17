/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/18 01:15:00 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

#define ICI printf("ICI\n");

/*####################### STRUCTURES #######################*/

typedef enum s_type
{
	CMD, // cmd								0
	ARG, // argument						1
	R_IN, // <								2
	R_OUT, // >								3
	DR_OUT, // >>							4
	DR_IN, // << (HERE_DOC)					5
	INFILE,	// word following <				6
	OUTFILE, // word following >			7
	LIMITOR, // word following <<			8
	OUTFILE_DROUT, // word following >>		9
	PIPE,//									10
}			t_type;


typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
}				t_quote;

typedef struct s_token
{
	char			*word;
	int				index;
	struct s_token	*next;
	enum s_type		type;
} 				t_token;

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
int		first_check(char *cmd_line);
void	manage_cmd(char *cmd_line);
void	tokenizer(char **cmd, t_token **lst);
int		second_check(t_token *lst);

	/*###   EXEC  ###*/

	/*###  UTILS  ###*/
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		is_sep(char c);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd, int i, t_quote *state);
int		next_squote_len(char *cmd, int i, t_quote *state);
int		is_whitespace(char c);
int		sp_word(char *cmd, int i, t_quote *state);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);
int		is_drout(t_token *tmp);
int		is_drin(t_token *tmp);
int		is_outfile_drout(t_token *save);
int		is_limitor(t_token *save);
int		is_type(t_token *tmp);

	/*### CLEANING ###*/
void	free_double_array(char **arr);


int	spr_word(char *cmd, int i);
int	spr_word2(char *cmd, int i, t_quote *state);
int	sep_word(char c);
int	quoting_rules(char *cmd, int i, t_quote *state);
int	end_word(char *cmd, int i, t_quote *state);

#endif
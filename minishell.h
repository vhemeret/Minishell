/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/20 01:27:01 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*####################### STRUCTURES #######################*/

typedef enum s_type
{
	CMD,	// cmd							0
	ARG,	// argument						1
	R_IN,	// <							2
	R_OUT,	// >							3
	DR_OUT,	// >>							4
	DR_IN, 	// << (HERE_DOC)				5
	FD,		// word following <				6
	PIPE,	//								7
}			t_type;


typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
}				t_quote;

typedef	struct s_expand
{
	char	*str;
	int		len;
	int		found;
}				t_expand;

typedef struct s_token
{
	char			*word;
	int				index;
	int				nb_words;
	struct s_token	*next;
	struct s_token	*back;
	enum s_type		type;
} 				t_token;

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
int		is_word(char *cmd, int i, t_quote *state);
int		end_word(char *cmd, int i, t_quote *state);
int		sep_word(char c);
int		first_check(char *cmd);
void	manage_cmd(char *cmd_line, char **env);
int		nb_words(char *cmd_line, t_quote *state);
void	tokenizer(char **cmd, t_token **lst, int len);
int		is_type(t_token *tmp);
int		syntax_check(t_token **lst);
int		check_quote(char *cmd_line, t_quote *state);
int		is_drout(t_token *tmp);
int		is_drin(t_token *tmp);
int		is_outfile_drout(t_token *save);
int		is_limitor(t_token *save);
void	expand(t_token **lst, t_quote *state, char **env);
char	**split_word(char *word, t_quote *state);


	/*###   EXEC  ###*/

	/*###  UTILS  ###*/
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd, int i, t_quote *state);
int		next_squote_len(char *cmd, int i, t_quote *state);
int		is_whitespace(char c);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);
char	**copy_env(char **env);
char	*ft_strcpy(char *src);
int		len_darr(char **arr);


	/*### CLEANING ###*/
void	free_double_array(char **arr);
int		print_and_free(char *str, t_token **lst);

// int	spr_word(char *cmd, int i);
// int	quoting_rules(char *cmd, int i, t_quote *state);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:24:16 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 18:06:23 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include <stdio.h>

# include "defines.h"
# include "libft.h"
# include "exec.h"
# include "env.h"
# include "shell.h"

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

// Utils
void		append_tokens(t_tokens **t1, t_tokens *t2);
size_t		delimiter(int *d_type, t_tokens *list, size_t i);
int			set_type(char *tmp);
int			is_falg(char *str);
int			cmd_specifier(char *str);
char		*minishell_getexec(char *execname, char **env);
int			specifier_two(char *str);
int			specifier_one(char *str);
char		*strjoin_and_free(char *s1, char *s2);

// HANDLE QUATATION

char		*get_expandet(char *str, t_env *env);
int			handle_quotes(t_tokens *tok, t_env *env);
int			redirection_quotes(char **str, t_env *env);

// Modules
t_wrap		*convert_str(char *str);
char		*convert_subfunction(char *str, t_wrap *list);

// Tokenisation helpers
t_tokens	*subtoken(t_tokens *list, size_t start, size_t end);
size_t		delimiter(int *d_type, t_tokens	*list, size_t i);
void		redirection(t_group *group, t_tokens	*list, size_t i);
int			lst_to_tokens(t_tokens *out, t_wrap *list, t_shell *shell);

// GROUPS HANDLE CMD
t_group		*handle_command_group(t_tokens *list, t_group *parrent, \
	size_t origin_i, size_t i);

// GROUPS HANDLE CMD UTILS
int			is_valid_cmd_position(t_tokens *list, size_t i);
t_group		*init_cmd_group(t_tokens *list, t_group *parrent, size_t i);
t_tokens	*get_command_tokens(t_tokens *list, size_t i, size_t j);
size_t		count_valid_tokens(t_tokens *sub);
t_tokens	*filter_tokens(size_t valid_count, t_group *group, \
	t_tokens *sub);

// GROUPS HANDLE CMD UTILS 2
int			copy_valid_tokens(t_tokens *filtered, \
	t_tokens *sub, t_group *group);
void		cleanup_filtered_tokens(t_tokens *fltrd, \
	t_tokens *sub, t_group *group);
void		setup_next_group(t_group *group, t_tokens *list, \
	size_t j, t_group *pnt);
t_group		*prepare_group(t_tokens *list, t_group *pnt, \
	size_t i, size_t *j_out);
t_tokens	*proc_cmd_tokens(t_group *group, t_tokens *list, \
	size_t i, size_t j);

// HANDLE BRACKETS
t_group		*handle_bracket_group(t_tokens *list, size_t i, size_t *j_out);
int			process_bracket_content(t_group *group, t_tokens *list, \
	size_t i, size_t *j);

// void		free_redirection(t_token *red); DEPRICATED
size_t		skip_special_tokens(t_tokens *list, size_t i);

// Create groups
t_group		*create_groups(t_tokens *list, t_group *parrent, size_t i, \
	size_t j);

// CHECK ERRORS BEFORE CREATING EXECUTION_LIST
int			parser_input_validation(t_tokens *tokens, t_shell *shell);

/**
 * @brief Parses and transforms a raw command string 
 * into an execution-ready group structure.
 * This function tokenizes the input string, validates it, 
 * parses it into grouped commands,
 * and fills the provided `t_group` structure with execution-related data.
 * It uses the following steps:
 * - Tokenizes the input with `wrap_operations()`.
 * - Validates tokens with `parser_input_validation()`.
 * - Parses token structure into command groups using `create_groups()`.
 * - Deduces the type of each command with `return_cmd_type()`.
 * - Frees all temporary allocations.
 * @param group Pointer to a pre-allocated t_group structure to be filled.
 * @param str Raw command-line string to be parsed and transformed.
 * @param env Array of environment variables used for expansions.
 * @return int Returns 0 on success, 1 on failure 
 * (invalid input or allocation error).
 * @see wrap_operations()
 * @see parser_input_validation()
 * @see create_groups()
 * @see return_cmd_type()
 */
int			create_execution_list(t_shell *shell, char *str);

// ERROR VISUALISATION DELETE AT PRODUCTION
void		print_tokens(t_tokens *tokens);
void		grouped_tokens_display(t_group *group);

#endif

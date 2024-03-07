#ifndef MSPARSING_H
# define MSPARSING_H

// PARSING
void	split_by_space(char *input, char ***split);
void	free_args(t_arg *args);
t_arg	*input_parser(char *input);

// INJECT_SPACE
char	*inject_space(char *input);

// REJOIN_TOKENS
t_arg	*rejoin_tokens(char ***in);

// SPLIT_BY_PIPE
char	***split_by_pipe(char **in);

// SPLIT_BY_SPACE
int		quotes(char c, char *reset);
void	cmd_assign(t_string *cmd, char input);
void	handle_space(t_string *cmd, char ***split, int *cmd_idx, int q);
char	**split_assign(char **split, int *cmd_idx, char *insert);
char	**cleanup_space(t_string *cmd, char ***split, int *cmd_idx);

#endif

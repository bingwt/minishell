#include "minishell.h"

int	is_dir(char *path)
{
	struct stat	s_statbuf;

	if (stat(path, &s_statbuf))
		return (0);
	return (S_ISDIR(s_statbuf.st_mode));
}

void	dir_check(t_arg *args, int i)
{
	if (!access(args[i].cmd[0], F_OK))
	{
		if (is_dir(args[i].cmd[0]))
			exit(handle_error(args[i].cmd[0], IS_DIR));
		else
			exit(handle_error(args[i].cmd[0], NO_PERMS_EXEC));
	}
	else
		exit(handle_error(args[i].cmd[0], NO_FILE_EXEC));
}

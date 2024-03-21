/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:10 by btan              #+#    #+#             */
/*   Updated: 2024/03/21 18:16:08 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	cd_oldpwd(char **oldpwd, char **pwd, t_list *envll)
//{
//	char	*temp;
//
//	*oldpwd = expand_env("$OLDPWD", envll);
//	printf("%s\n", *oldpwd);
//	chdir(*oldpwd);
//	temp = ft_strjoin("export OLDPWD=", *pwd);
//	ft_export(temp, &envll);
//	free(temp);
//	*pwd = ft_pwd();
//	temp = ft_strjoin("export PWD=", *pwd);
//	ft_export(temp, &envll);
//	free(temp);
//	free(*oldpwd);
//}

static void	cd_shortcut(const char *path, t_list *envll)
{
	char	**temp;

	temp = ft_calloc(2, sizeof(char *));
	*temp = ft_strre((char *) path, "~", getenv("HOME"));
	ft_cd(temp, envll);
	free(*temp);
	free(temp);
}

static void	set_oldpwd(char **cwd, char **oldpwd, t_list *envll)
{
	char	**temp;

	temp = ft_calloc(2, sizeof(char *));
	*temp = ft_strjoin("PWD=", *cwd);
	ft_export(temp, &envll);
	free(*temp);
	*temp = ft_strjoin("OLDPWD=", *oldpwd);
	ft_export(temp, &envll);
	free(*temp);
	free(*oldpwd);
	free(*cwd);
	free(temp);
}

void	ft_cd(char **args, t_list *envll)
{
	char	*oldpwd;
	char	*cwd;

	if (ft_strslen(args) > 1)
	{
		get_exit_status(unshift_exitcode(handle_error("cd", "TOO_MANY_ARGS")));
		return ;
	}
	if (!args[0])
	{
		cd_shortcut("~", envll);
		return ;
	}
	if (ft_strchr(args[0], '~'))
	{
		cd_shortcut(args[0], envll);
		return ;
	}
	oldpwd = ft_pwd();
	if (chdir(args[0]))
	{
		free(oldpwd);
		ft_printf_fd(2, "minibing: cd: ");
		perror(args[0]);
		get_exit_status(unshift_exitcode(1));
		return ;
	}
	cwd = ft_pwd();
	set_oldpwd(&cwd, &oldpwd, envll);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:10 by btan              #+#    #+#             */
/*   Updated: 2024/04/07 18:13:10 by btan             ###   ########.fr       */
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

	temp = ft_calloc(3, sizeof(char *));
	temp[0] = "cd";
	temp[1] = ft_strre((char *) path, "~", getenv("HOME"));
	ft_cd(temp, envll);
	free(temp[1]);
	free(temp);
}

static void	set_oldpwd(char **cwd, char **oldpwd, t_list *envll)
{
	char	**temp;

	temp = ft_calloc(3, sizeof(char *));
	temp[0] = "export";
	temp[1] = ft_strjoin("PWD=", *cwd);
	ft_export(temp, &envll);
	free(temp[1]);
	temp[1] = ft_strjoin("OLDPWD=", *oldpwd);
	ft_export(temp, &envll);
	free(temp[1]);
	free(*oldpwd);
	free(*cwd);
	free(temp);
}

void	ft_cd(char **args, t_list *envll)
{
	char	*oldpwd;
	char	*cwd;

	if (ft_strslen(args) > 2)
	{
		handle_error("cd", TOO_MANY_ARGS);
		return ;
	}
	if (!args[1] || ft_strchr(args[1], '~'))
	{
		cd_shortcut("~", envll);
		return ;
	}
	oldpwd = get_cwd();
	if (chdir(args[1]))
	{
		free(oldpwd);
		ft_putstr_fd("minibing: cd: ", 2);
		perror(args[1]);
		get_exit_status(unshift_exitcode(1));
		return ;
	}
	cwd = get_cwd();
	set_oldpwd(&cwd, &oldpwd, envll);
}

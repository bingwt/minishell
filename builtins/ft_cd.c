/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:10 by btan              #+#    #+#             */
/*   Updated: 2024/03/06 20:54:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*temp;

	temp = ft_strre((char *) path, "~", getenv("HOME"));
	ft_cd(temp, envll);
	free(temp);
}

static void	set_oldpwd(char **cwd, char **oldpwd, t_list *envll)
{
	char	*temp;

	temp = ft_strjoin("export PWD=", *cwd);
	ft_export(temp, &envll);
	free(temp);
	temp = ft_strjoin("export OLDPWD=", *oldpwd);
	ft_export(temp, &envll);
	free(temp);
	free(*oldpwd);
	free(*cwd);
}

void	ft_cd(const char *path, t_list *envll)
{
	char	*pwd;
	char	*oldpwd;
	char	*cwd;

	if (!*path)
		return ;
	pwd = ft_pwd();
	if (ft_strchr(path, '~'))
	{
		cd_shortcut(path, envll);
		return ;
	}
	oldpwd = ft_pwd();
	if (chdir(path))
	{
		free(oldpwd);
		ft_printf_fd(2, "minibing: cd: ");
		perror(path);
		get_exit_status(unshift_exitcode(1));
		return ;
	}
	cwd = ft_pwd();
	set_oldpwd(&cwd, &oldpwd, envll);
}

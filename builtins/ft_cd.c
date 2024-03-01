/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:10 by btan              #+#    #+#             */
/*   Updated: 2024/03/01 15:25:05 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(const char *path, t_list *envll)
{
	char	*pwd;
	char	*oldpwd;
	char	*cwd;
	char	*temp;

	if (!*path)
		return ;
	pwd = ft_pwd();
	if (ft_strchr(path, '-'))
	{
		oldpwd = expand_env("$OLDPWD", envll);
		printf("%s\n", oldpwd);
		chdir(oldpwd);
		temp = ft_strjoin("export OLDPWD=", pwd);
		ft_export(temp, &envll);
		free(temp);
		pwd = ft_pwd();
		temp = ft_strjoin("export PWD=", pwd);
		ft_export(temp, &envll);
		free(temp);
		free(oldpwd);
		return ;
	}
	if (ft_strchr(path, '~') && ft_strlen(path) == 1)
	{
		ft_cd(getenv("HOME"), envll);
		return ;
	}
	oldpwd = ft_pwd();
	if (chdir(path))
	{
		free(oldpwd);
		ft_printf_fd(2, "minibing: cd: ");
		perror(path);
		return ;
	}
	cwd = ft_pwd();
	temp = ft_strjoin("export PWD=", cwd);
	ft_export(temp, &envll);
	free(temp);
	temp = ft_strjoin("export OLDPWD=", oldpwd);
	ft_export(temp, &envll);
	free(temp);
	free(oldpwd);
	free(cwd);
}

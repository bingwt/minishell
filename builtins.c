/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:25:03 by btan              #+#    #+#             */
/*   Updated: 2024/02/28 02:05:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(const char *str)
{
	if (!ft_strncmp("-n", str, 2))
		printf("%s", str + 3);
	else
		printf("%s\n", str);
}

void	ft_cd(const char *path)
{
	chdir(path);
}

char	*ft_pwd(void)
{
	char	*path;

	path = malloc(PATH_MAX + 1 * (sizeof(char)));
	if (!path)
		return (NULL);
	path[PATH_MAX] = '\0';
	getcwd(path, PATH_MAX);
	return (path);
}

void	ft_env(char **envp)
{
	while (*envp)
		printf("%s\n", *(envp++));
}

void	ft_export(char *cmd, t_list **envll)
{
	t_list	*env;
	char	**args;
	char	*content;
	char	*token;
	
	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	while (env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(token + 7, content, ft_strchr(content, '=') - content))
			break ;
		env = env->next;
	}
	free_strs(args);
	if (env)
	{
		printf("Already exists!\n");
		return ;
	}
	if (!env && ft_strchr(cmd, '='))
	{
		env = ft_lstnew(ft_strdup(cmd + 7));
		ft_lstadd_back(envll, env);
	}
	else
	{
		env = *envll;
		while (env)
		{
			printf("declare -x %s\n", (char *) env->content);
			env = env->next;
		}
	}
}

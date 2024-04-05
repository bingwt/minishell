/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:00:36 by btan              #+#    #+#             */
/*   Updated: 2024/04/04 16:23:57 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list **envll)
{
	t_list	*env;
	char	*content;
	char	*end;
	char	**var;
	int		i;

	env = *envll;
	while (env)
	{
		content = (char *) env->content;
		end = ft_strchr(content, '=');
		var = ft_calloc(3, sizeof(char *));
		var[0] = ft_substr(content, 0, end - content);
		var[1] = ft_substr(end, 1, ft_strlen(end));
		if (!ft_strchr(content, '='))
			printf("declare -x %s\n", var[0]);
		else if (!var[1])
			printf("declare -x %s=\"\"\n", var[0]);
		else
		{
			i = -1;
			while (var[1][++i])
				if (var[1][i] == '$')
					var[1] = ft_strre(&var[1][i], "$", "\\$");
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		}
		env = env->next;
		free_strs(var);
	}
}

int	valid_token(char *token)
{
	if (!token)
	{
		handle_error("=", NOT_VALID_ID);
		return (0);
	}
	if (ft_isalpha(*token) || *token == '_')
		token++;
	else
	{
		handle_error(token, NOT_VALID_ID);
		return (0);
	}
	while (*token)
	{
		if (!ft_isalnum(*token) && *token != '_')
		{
			handle_error(token, NOT_VALID_ID);
			return (0);
		}
		token++;
	}
	return (1);
}

static t_list	*find_token(char *token, t_list *env)
{
	char	*start;
	char	*end;
	char	*env_token;

	while ((token[0] != '\0') && env)
	{
		start = (char *) env->content;
		end = ft_strchr(start, '=');
		env_token = ft_substr(start, 0, end - start);
		if (!ft_strcmp(token, env_token))
		{
			free(env_token);
			break ;
		}
		free(env_token);
		env = env->next;
	}
	return (env);
}

void	export_var(char *cmd, t_list **envll)
{
	t_list	*env;
	char	**args;
	char	*token;

	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	if (!valid_token(token))
		return ;
	env = find_token(token, env);
	free_strs(args);
	if (env)
	{
		if (!ft_strchr(cmd, '='))
			return ;
		env->content = ft_strdup(cmd);
		return ;
	}
	if (!env)
	{
		env = ft_lstnew(ft_strdup(cmd));
		ft_lstadd_back(envll, env);
	}
}

void	ft_export(char **args, t_list **envll)
{
	int		i;

	i = 1;
	if (!args[1])
		print_env(envll);
	else
		while (args[i])
			export_var(args[i++], envll);
}

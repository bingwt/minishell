/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:55:23 by btan              #+#    #+#             */
/*   Updated: 2024/04/05 23:19:38 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_var(char *token, t_list *env)
{
	char	*content;

	while (env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(token, content, ft_strchr(content, '=') - content))
			break ;
		env = env->next;
	}
	return (env);
}

static t_list	*find_prev_var(t_list *var, t_list *env)
{
	while (env->next != var)
	{
		env = env->next;
		if (!env)
			break ;
	}
	return (env);
}

void	unset_var(char *cmd, t_list **envll)
{
	t_list	*var;
	t_list	*env;
	char	**args;

	var = *envll;
	env = *envll;
	args = ft_split(cmd, '=');
	var = find_var(args[0], env);
	ft_free_split(&args);
	if (var)
	{
		env = find_prev_var(var, env);
		if (!env)
		{
			*envll = (*envll)->next;
			ft_lstdelone(var, free);
			return ;
		}
		env->next = env->next->next;
		ft_lstdelone(var, free);
	}
	return ;
}

void	ft_unset(char **args, t_list **envll)
{
	int	i;

	i = 1;
	if (!args[1])
		return ;
	else
		while (args[i])
			unset_var(args[i++], envll);
}

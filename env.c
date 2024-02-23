/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 08:21:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(void)
{
	char	**env;

	env = ft_calloc(4, sizeof(char *));
	env[0] = ft_strjoin("PWD=", getenv("PWD"));
	env[1] = ft_strjoin("TERM=", getenv("TERM"));
	env[2] = ft_strjoin("DISPLAY=", getenv("DISPLAY"));
	return (env);
}

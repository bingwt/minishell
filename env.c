/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 17:20:03 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(void)
{
	char	**env;

	env = ft_calloc(9, sizeof(char *));
	env[0] = ft_strjoin("USER=", getenv("USER"));
	env[1] = ft_strjoin("HOME=", getenv("HOME"));
	env[2] = ft_strjoin("PWD=", getenv("PWD"));
	env[3] = ft_strjoin("DISPLAY=", getenv("DISPLAY"));
	env[4] = ft_strjoin("TERM=", getenv("TERM"));
	env[5] = ft_strjoin("PATH=", getenv("PATH"));
	env[6] = ft_strjoin("DBUS_SESSION_BUS_ADDRESS=", \
	getenv("DBUS_SESSION_BUS_ADDRESS"));
	env[7] = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:59:25 by btan              #+#    #+#             */
/*   Updated: 2024/02/29 21:55:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*ptr;

	fd = open("/etc/hostname", O_RDONLY);
	hostname = ft_calloc(1025, 1);
	if (!hostname)
		return (NULL);
	hostname[1024] = '\0';
	read(fd, hostname, 1024);
	ptr = hostname;
	while (*ptr)
	{
		if (*ptr == '.' || *ptr == '\n')
			*ptr = '\0';
		ptr++;
	}
	close(fd);
	return (hostname);
}

static char	*get_user(t_list *envll)
{
	char	*user;
	char	*temp;
	char	*hostname;

	user = expand_env("$USER", envll);
	temp = ft_strjoin("\033\e[46m\002", user);
	free(user);
	user = ft_strjoin(temp, "@");
	free(temp);
	temp = get_hostname();
	hostname = ft_strjoin(temp, ":");
	free(temp);
	temp = ft_strjoin(user, hostname);
	free(user);
	free(hostname);
	return (temp);
}

char	*init_prompt(t_list *envll)
{
	char	*userhost;
	char	*pwd;
	char	*home;
	char	*temp;
	char	*prompt;

	userhost = get_user(envll);
	temp = ft_pwd();
	pwd = ft_strjoin(temp, "$\001\e[0m\002 ");
	home = expand_env("$HOME", envll);
	free(temp);
	if (*home == '\n')
		temp = ft_strjoin(userhost, "~");
	else
		temp = ft_strjoin(userhost, "");
	prompt = ft_strjoin(temp, pwd + ft_strlen(home));
	free(temp);
	free(userhost);
	free(pwd);
	return (prompt);
}

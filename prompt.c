/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:59:25 by btan              #+#    #+#             */
/*   Updated: 2024/02/21 20:32:49 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
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

char	*get_user(void)
{
	char	*user;
	char	*temp;
	char	*hostname;

	temp = ft_strjoin("\033\e[46m\002", getenv("USER"));
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

char	*init_prompt(void)
{
	char	*userhost;
	char	*pwd;
	char	*temp;
	char	*prompt;

	userhost = get_user();
	temp = ft_pwd();
	pwd = ft_strjoin(temp, "$ ");
	free(temp);
	if (!strncmp(getenv("HOME"), pwd, ft_strlen(getenv("HOME"))))
	{
		temp = ft_strjoin(userhost, "~");
		prompt = ft_strjoin(temp, pwd + ft_strlen(getenv("HOME")));
		free(temp);
	}
	else
		prompt = ft_strjoin(userhost, pwd);
	free(userhost);
	free(pwd);
	temp = ft_strjoin(prompt, "\001\e[0m\002");
	free(prompt);
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:37:38 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/06 11:46:00 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_st("fork:", "Cannot allocate memory", 1);
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		error_st("pipe:", "Too many open files", 1);
}

int	ft_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	g_minishell.exit_status = 127;
	return (0);
}

void	ft_wait_all(void)
{
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
}

void	ft_wait_for_childs(t_cmd **cmds)
{
	int		status;
	t_cmd	*ps;

	ps = *cmds;
	sig_ignore();
	while (ps->next)
		ps = ps->next;
	if (ps->pid && ps->pid > 0)
	{
		waitpid(ps->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (ps->infile && ps->infile[0][0] == '<' && ps->infile[0][0] == '<'\
			&& ps->ctl_c_hd == 1)
				g_minishell.exit_status = 1;
			else
				g_minishell.exit_status = (128 + WTERMSIG(status));
			if (WTERMSIG(status) == 3 && !ps->next)
				write(1, "Quit: 3", 7);
			write(1, "\n", 1);
		}
	}
	ft_wait_all();
	sig_parent();
}

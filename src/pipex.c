/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:55:01 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/26 23:18:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_execute(t_data *data, int cmd_index, int num_cmds)
{
	if (cmd_index < num_cmds - 1)
		if (pipe(data->fd) == -1)
			free_all_stop(data, 0, 1, "1");
	data->pid[cmd_index] = fork();
	if (data->pid[cmd_index] == -1)
		free_all_stop(data, 0, 1, "1");
	if (data->pid[cmd_index] == 0 && data->input_fd != -5)
		child(data, cmd_index, num_cmds);
	else
		parent(data, cmd_index, num_cmds);
}

void	child(t_data *data, int cmd_index, int num_cmds)
{
	if (data->input_fd != STDIN_FILENO)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			free_all_stop(data, 0, 1, "1");
		close(data->input_fd);
	}
	if (cmd_index < num_cmds - 1)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			free_all_stop(data, 0, 1, "1");
		close(data->fd[0]);
		close(data->fd[1]);
	}
	else
		redirect_output(data);
	data->split = ft_split(data->cmd[cmd_index], ' ');
	get_cmd(data, data->envp, data->split[0]);
	if (execve(data->path, data->split, data->envp) == -1)
		free_all_stop(data, 0, 1, "1");
	data->split = ft_free_str(data->split);
}

void	parent(t_data *data, int cmd_index, int num_cmds)
{
	int	i;

	if (data->input_fd != -5 && data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	if (cmd_index < num_cmds - 1)
	{
		close(data->fd[1]);
		data->input_fd = data->fd[0];
		ft_execute(data, cmd_index + 1, num_cmds);
		close(data->fd[0]);
	}
	i = 0;
	while (i <= cmd_index)
		waitpid(data->pid[i++], &data->error, 0);
}

static void	init(t_data *data, int *argc, char ***argv)
{
	int	i;

	data->cmd = ft_calloc(*argc - 2, sizeof(char *));
	data->pid = ft_calloc(*argc - 2, sizeof(char *));
	if (!data->cmd)
		free_all_stop(data, 0, 1, NULL);
	if (data->limiter == NULL)
	{
		data->infile = (*argv)[1];
		data->input_fd = open(data->infile, O_RDONLY);
		if (data->input_fd == -1)
		{
			ft_putstr_fd("no such a file or directory\n", 1);
			data->input_fd = -5;
		}
	}
	data->outfile = (*argv)[*argc - 1];
	i = -1;
	while (++i < *argc - 3)
		data->cmd[i] = (*argv)[i + 2];
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Not enough arguments. \
			Usage: infile \"command 1\" \"command 2\" output file\n", 1);
		return (1);
	}
	data.error = 0;
	data.envp = envp;
	data.pid = NULL;
	data.path = NULL;
	data.split = NULL;
	data.limiter = NULL;
	data.cmd = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(&data, &argc, &argv);
	init(&data, &argc, &argv);
	ft_execute(&data, 0, argc - 3);
	close(data.input_fd);
	free_all_stop(&data, 0, WEXITSTATUS(data.error), NULL);
	return (0);
}

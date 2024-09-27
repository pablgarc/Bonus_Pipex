/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:45:13 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/26 23:18:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_all_stop(t_data *data, int is_malloc, int error, char *message)
{
	if (data->limiter)
		unlink(FILE_TEMP);
	if (data->path)
		free(data->path);
	if (data->cmd)
		free(data->cmd);
	if (data->pid)
		free(data->pid);
	if (data->split)
		data->split = ft_free_str(data->split);
	if (error)
	{
		if (message && (*message == '1' || *message == '2'))
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		else if (message)
		{
			write(STDERR_FILENO, message, ft_strlen(message));
			if (message[ft_strlen(message) - 1] != '\n')
				write(STDERR_FILENO, "\n", 1);
		}
		if (is_malloc)
			free(message);
		exit(error);
	}
	exit(EXIT_SUCCESS);
}

void	redirect_output(t_data *data)
{
	int	outfile_fd;

	if (data->limiter)
		outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		free_all_stop(data, 0, 1, "1");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		close(outfile_fd);
		free_all_stop(data, 0, 1, "1");
	}
	if (close(outfile_fd) == -1)
		perror("Failed to close the file descriptor");
}

void	get_cmd(t_data *data, char **envp, char *cmd)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		free_all_stop(data, 0, 1, "Failed to allocate memory\n");
	i = -1;
	while (path[++i])
	{
		get_path(data, cmd, path[i]);
		if (access(data->path, 0) == 0)
			break ;
		free(data->path);
		data->path = NULL;
	}
	path = ft_free_str(path);
	if (!data->path)
		free_all_stop(data, 1, 127, ft_strjoinf("zsh: command not found: ", cmd,
				0));
}

void	get_path(t_data *data, char *cmd, char *path)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		data->path = ft_strdup(cmd);
	else
	{
		data->path = ft_strjoinf(path, "/", 0);
		data->path = ft_strjoinf(data->path, cmd, 1);
	}
}

void	here_doc(t_data *data, int *argc, char ***argv)
{
	char	*line;

	data->limiter = argv[0][2];
	data->infile = FILE_TEMP;
	*argc = *argc - 1;
	*argv = *argv + 1;
	data->input_fd = open(FILE_TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->input_fd == -1)
		free_all_stop(data, 0, 1, "1");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			free_all_stop(data, 0, 1, "1");
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0)
			if (ft_strlen(line) - 1 == ft_strlen(data->limiter))
				break ;
		write(data->input_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(data->input_fd);
	data->input_fd = open(FILE_TEMP, O_RDONLY);
}

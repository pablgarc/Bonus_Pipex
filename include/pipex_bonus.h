/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:52:07 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/29 08:52:00 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FILE_TEMP ".here_doc_tmp"

typedef struct s_data
{
	char	*path;
	char	**envp;
	char	**split;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**cmd;
	int		fd[2];
	int		input_fd;
	int		*pid;
	int		error;
}			t_data;

// pipex.c
void		ft_execute(t_data *data, int cmd_index, int num_cmds);
void		child(t_data *data, int cmd_index, int num_cmds);
void		parent(t_data *data, int cmd_index, int num_cmds);

// tools.c
void		ft_free(t_data *data, int is_malloc, int error,
				char *message);
void		redirect_output(t_data *data);
void		get_cmd(t_data *data, char **envp, char *cmd);
void		get_cmd_from_path(t_data *data, char *cmd, char **envp);
void		get_path(t_data *data, char *cmd, char *path);
void		here_doc(t_data *data, int *ac, char ***av);
int			check_direct_path(t_data *data, char *cmd);

#endif
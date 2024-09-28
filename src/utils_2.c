/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:27:20 by pablo             #+#    #+#             */
/*   Updated: 2024/09/28 23:33:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_direct_path(t_data *data, char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.' || data->envp == NULL || *data->envp == NULL)
	{
		data->path = ft_strdup(cmd);
		if (access(data->path, X_OK) == 0) // Verificar si es ejecutable
			return (1); // Ruta encontrada, salida de la función principal
		else
		{
			free_all_stop(data, 1, 127, ft_strjoinf("zsh: command not found: ", cmd, 0));
			return (1); // Retorno 1 ya que se ha encontrado o se lanza error
		}
	}
	return (0); // No es una ruta directa, continuar la búsqueda en PATH
}

void	get_cmd_from_path(t_data *data, char *cmd, char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i]) // No hay PATH en envp
		free_all_stop(data, 1, 127, "No PATH in environment");

	path = ft_split(envp[i] + 5, ':');
	if (!path)
		free_all_stop(data, 0, 1, "Failed to allocate memory\n");

	i = -1;
	while (path[++i])
	{
		get_path(data, cmd, path[i]);
		if (access(data->path, X_OK) == 0)
			break ;
		free(data->path);
		data->path = NULL;
	}

	path = ft_free_str(path);
	if (!data->path)
		free_all_stop(data, 1, 127, ft_strjoinf("zsh: command not found: ", cmd, 0));
}

void	get_cmd(t_data *data, char **envp, char *cmd)
{
	if (check_direct_path(data, cmd)) // Verifica si es una ruta directa
		return;
	get_cmd_from_path(data, cmd, envp); // Si no, busca en el PATH
}

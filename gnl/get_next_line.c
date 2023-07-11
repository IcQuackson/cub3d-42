/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:25:45 by joao-per          #+#    #+#             */
/*   Updated: 2023/02/23 21:25:45 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strchrz(char c, char *line)
{
	if (!line)
		return (0);
	while (*line)
		if (*line++ == c)
			return (1);
	return (0);
}

size_t	ft_strlenz(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	clean(char *stash)
{
	int	i;
	int	j;

	i = ft_strlenz(stash);
	j = 0;
	while (stash[i])
		stash[j++] = stash[i++];
	while (stash[j])
		stash[j++] = '\0';
}

char	*ft_strjoinz(char *line, char *buff)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((ft_strlenz(line) + ft_strlenz(buff) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (line && line[j])
		str[i++] = line[j++];
	j = 0;
	while (buff && buff[j] && buff[j] != '\n')
		str[i++] = buff[j++];
		/* if (buff[j] == '\r')
			break ; */
	if (buff[j] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	stash[2];
	char		*line;

	line = NULL;
	if (fd < 0)
		return (0);
	while (stash[0] || read(fd, stash, 1) > 0)
	{
		if (ft_strchrz('\n', stash))
		{
			line = ft_strjoinz(line, "\n");
			clean(stash);
			break ;
		}
		line = ft_strjoinz(line, stash);
		clean(stash);
	}
	return (line);
}
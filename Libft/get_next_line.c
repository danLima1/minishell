/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:30:37 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/26 19:11:31 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*read_file(int fd, char *save)
{
	ssize_t	i;
	char	*buffer;

	i = 1;
	buffer = (char *) malloc(BUFFER_SIZE + 2 * sizeof(char));
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0)
			break ;
		else if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		save = ft_strjoin(save, buffer);
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buffer);
	if (!save || save[0] == '\0')
		return (NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*temp;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = ft_substr(save, 0, i + 1);
	temp = ft_substr(save, i + 1, (ft_strlen(save) - (i)));
	if (!temp || temp[0] == '\0')
	{
		free(save);
		save = NULL;
		free(temp);
		return (line);
	}
	free(save);
	save = ft_strdup(temp);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>
int main()
{
	char	*a;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	a = get_next_line(fd);
	printf("A: %s", a);
	free(a);
	a = get_next_line(fd);
	printf("A: %s", a);
	free(a);
	a = get_next_line(fd);
	printf("A: %s", a);
	free(a);
	a = get_next_line(fd);
    printf("A: %s", a);
	free(a);
	a = get_next_line(fd);
    printf("A: %s", a);
	free(a);
}*/
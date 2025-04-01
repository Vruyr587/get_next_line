/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:26 by vrasatry          #+#    #+#             */
/*   Updated: 2025/03/31 18:24:05 by tasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_rest_trimmer(char *s)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (s[count] != '\0' && s[count] != '\n')
		count++;
	if (s[count] == '\n')
		count++;
	str = (char *)malloc(sizeof(char) * (count + 1));
	while (count != 0)
	{
		str[i] = s[i];
		i++;
		count--;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_rest_keeper(char *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i] || !s[i + 1])
		return (ft_freenull(s), NULL);
	if (s[i] == '\n')
		i++;
	len = ft_strlen(&s[i]);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	len = -1;
	while (s[i] != '\0')
		str[++len] = s[i++];
	str[len + 1] = '\0';
	ft_freenull(s);
	return (str);
}

static char	*ft_storage_filler(int fd, int count, char *tmp, char *buffer)
{
	char	*new_buffer;

	while (count)
	{
		count = read(fd, tmp, BUFFER_SIZE);
		if (count == -1)
			return (NULL);
		else if (count == 0)
			break ;
		tmp[count] = '\0';
		new_buffer = buffer;
		buffer = ft_strjoin(new_buffer, tmp);
		ft_freenull(new_buffer);
		new_buffer = NULL;
		if (!buffer)
			return (ft_freenull(tmp), NULL);
		if (ft_strchr(tmp, '\n') != NULL)
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*rest;
	char		*tmp;
	int			count;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tmp = (char *)malloc((sizeof(char) * (BUFFER_SIZE + 1)));
	if (!tmp)
		return (NULL);
	count = 1;
	buffer = ft_storage_filler(fd, count, tmp, buffer);
	if (!buffer)
		return (ft_freenull(tmp), NULL);
	ft_freenull(tmp);
	rest = ft_rest_trimmer(buffer);
	buffer = ft_rest_keeper(buffer);
	return (rest);
}

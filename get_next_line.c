/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:07:09 by mimatsub          #+#    #+#             */
/*   Updated: 2023/01/13 00:54:40 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*error(char **line, char **save)
{
	if (save != NULL && *save)
	{
		free(*save);
		*save = NULL;
	}
	if (line != NULL && *line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

static char	*ft_strjoin_n(char const *line, char const *s, size_t n)
{
	size_t	len;
	size_t	len1;
	char	*tmp;

	if (!line || !s)
		return (NULL);
	len1 = ft_strlen(line);
	if (n == 0)
		len = len1 + ft_strlen(s) + 1;
	else
		len = len1 + n + 1;
	tmp = (char *)malloc(sizeof(char) * len);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, line, len1 + 1);
	ft_strlcat(tmp, s, len);
	return (tmp);
}

static int	put_line_save(char **line, char **save, char *buf, ssize_t r_len)
{
	char	*tmp;
	int		flag;
	ssize_t	n;

	if (r_len != 0)
		buf[r_len] = '\0';
	n = ft_strchar_n(buf);
	tmp = ft_strjoin_n(*line, buf, n);
	if (!tmp)
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	flag = 0;
	if (n > 0 && buf[n - 1] == '\n')
	{
		tmp = ft_strdup(buf + n);
		if (!tmp)
			return (-1);
		flag = 1;
	}
	free(*save);
	*save = tmp;
	return (flag);
}

static char	*ini_setting(int fd, char *save, char **buf)
{
	char	*line;

	if (fd < 0 || FOPEN_MAX < fd || BUFFER_SIZE < 1)
		return (error(NULL, &save));
	line = malloc(1);
	if (!line)
		return (error(NULL, &save));
	line[0] = '\0';
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (!*buf)
		return (error(&line, &save));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buf;
	int			flag;
	ssize_t		n;

	flag = 0;
	n = 1;
	buf = NULL;
	line = ini_setting(fd, save, &buf);
	if (!line)
		return (NULL);
	if (save)
		flag = put_line_save(&line, &save, save, 0);
	while (flag == 0 && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			break ;
		flag = put_line_save(&line, &save, buf, n);
	}
	free(buf);
	if (flag == -1 || (!save && line[0] == '\0') || n < 0)
		return (error(&line, &save));
	return (line);
}

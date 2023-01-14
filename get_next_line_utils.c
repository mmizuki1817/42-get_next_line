/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:43:32 by mimatsub          #+#    #+#             */
/*   Updated: 2022/12/23 02:45:49 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while (n > 1 && *src != '\0')
	{
		*dst++ = *src++;
		n--;
	}
	*dst = '\0';
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		len;
	size_t		i;
	size_t		j;

	if (dst == NULL && size == 0)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
	{
		len = src_len + size;
		return (len);
	}
	i = dst_len;
	j = 0;
	while (size - dst_len > 1 && src[j] != '\0')
	{
		dst[i++] = src[j++];
		size--;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(s);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, len + 1);
	return (dest);
}

size_t	ft_strchar_n(const char *s)
{
	size_t	n;
	char	*tmp;

	tmp = (char *)s;
	n = 0;
	while (tmp[n] != '\0')
	{
		if (tmp[n] == '\n')
			return (n + 1);
		n++;
	}
	return (0);
}

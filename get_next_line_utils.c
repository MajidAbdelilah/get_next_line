/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:11:53 by amajid            #+#    #+#             */
/*   Updated: 2023/11/14 15:57:36 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long	ft_strlen(const char *s)
{
	long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, long n)
{
	long			i;
	unsigned char	*dest_h;
	unsigned char	*src_h;

	if (!dest && !src)
		return (dest);
	i = 0;
	dest_h = (unsigned char *)dest;
	src_h = (unsigned char *)src;
	while (i < n)
	{
		dest_h[i] = src_h[i];
		i++;
	}
	return (dest);
}

long	ft_strlcpy(char *dst, const char *src, long dstsize)
{
	long	i;

	if (!dstsize)
	{
		if (src)
			return (ft_strlen(src));
		else
			return (0);
	}
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	i++;
	return (i);
}

void	ft_bzero(void *s, long n)
{
	long	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
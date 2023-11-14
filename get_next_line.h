/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:54:55 by amajid            #+#    #+#             */
/*   Updated: 2023/11/14 15:58:09 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif


char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, long n);
long	ft_strlen(const char *s);
long	ft_strlcpy(char *dst, const char *src, long dstsize);
void	ft_bzero(void *s, long n);

#endif
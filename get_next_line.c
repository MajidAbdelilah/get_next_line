/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:48:33 by amajid            #+#    #+#             */
/*   Updated: 2023/11/14 18:10:46 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>

char *get_next_line(int fd)
{
	static char *buffer;
	static char *buffer_swap;
	char *ret_buf;
	static char is_1_call;
	static int i;
	static int j;
	static int start;
	static int read_ret;
	static long size;

	ret_buf = 0;
	if(is_1_call && !buffer)
	{
		buffer = 0;
		buffer_swap = 0;
		is_1_call = 0;
		i = 0;
		j = 0;
		start = 0;
		read_ret = 0;
		size = 1000000;	
	}
	if(!is_1_call)
	{
		size = 1000000;
		buffer = malloc(size);
		if(!buffer)
			return NULL;
	}
		
	if(!read_ret && is_1_call)
	{
		return NULL;
	}
	start = j;
	while(((read_ret) && read_ret != -1 )|| !is_1_call)
	{
			while((j) < i)
		{
	//printf("c = %c, read_ret = %d\n", buffer[j], read_ret);
			if(buffer[j] == '\n')
			{
				ret_buf = malloc(j - start + 2);
				if(!ret_buf)
				{
					free(buffer);
					buffer = NULL;
					is_1_call = 1;
					return NULL;
				}
				ft_strlcpy(ret_buf, buffer + start, j - start + 2);
				is_1_call = 1;
				j++;
				return ret_buf;
			}
			j++;
		}
		if((BUFFER_SIZE + 1000) >= (size - i))
		{
			//printf("here!!!!!!!!!!!!!!!!!!!!!!!!\n");
			buffer_swap = buffer;
			buffer = malloc((i + BUFFER_SIZE) * 4 + size );
			size = (i + BUFFER_SIZE) * 4 + size;
			if(!buffer)
			{
				free(buffer_swap);
				return NULL;
			}
			if(buffer_swap)
			{
				ft_memcpy(buffer, buffer_swap, i);
				free(buffer_swap);
			}
			buffer_swap = NULL;
		}
		//printf("i = %d\n", i);
		read_ret = read(fd, buffer + i, BUFFER_SIZE);
		i += read_ret;
		//printf("read_ret = %d\n", read_ret);
		
		if(read_ret == -1)
		{
			//ft_bzero(buffer, i);
			free(buffer);
			buffer = NULL;
			is_1_call = 1;
			return NULL;
		}
		
		while((j) < i)
		{
			if(buffer[j] == '\n')
			{
				ret_buf = malloc(j - start + 2);
				if(!ret_buf)
				{
					free(buffer);
					buffer = NULL;
					is_1_call = 1;
					return NULL;
				}
				ft_strlcpy(ret_buf, buffer + start, j - start + 2);
				is_1_call = 1;
				j++;
				return ret_buf;
			}
			j++;
		}
	//printf("j = %d\n", j);	
		if(!read_ret && buffer[(j - 1) * (j > 0)] != '\n' && j)
		{
	//printf("c = %c, j = %d, i = %d, read_ret = %d, start = %d\n", buffer[j - 1], j, i, read_ret, start);
			ret_buf = malloc(j - start + 1);
			if(!ret_buf)
			{
				free(buffer);
				buffer = NULL;
				is_1_call = 1;
				return NULL;
			}
				ft_strlcpy(ret_buf, buffer + start, j - start + 1);
				is_1_call = 1;
				j++;
				free(buffer);
				buffer = NULL;
				return ret_buf;
		}
		if(!j)
		{
			free(buffer);
			buffer = NULL;
			return NULL;
		}
		//j = i;
	}
	if(read_ret == -1)
	{
		//printf("buffer = %p\n", buffer);
		if(buffer)
			free(buffer);
		buffer = NULL;
		return (0);	
	}
		if(!read_ret && buffer[j - 1] == '\n')
		{
			if(buffer)
				free(buffer);	
			buffer = NULL;
		}
			if(buffer)
				free(buffer);	
			buffer = NULL;
		
	//printf("j = %d, start = %d\n", j, start);
		//printf("i = %d\n", i);
	//ret_buf = malloc(j - start + 1);
	//ft_strlcpy(ret_buf, buffer, j - start + 1);
	is_1_call = 1;
	return NULL;
}
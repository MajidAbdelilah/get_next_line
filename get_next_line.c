/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:48:33 by amajid            #+#    #+#             */
/*   Updated: 2023/11/17 17:36:56 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>


static char is_nl(t_vars *v)
{
	while(((*v).j) < (*v).i)
	{
		if((*v).buffer[(*v).j] == '\n')
		{
			(*v).ret_buf = malloc((*v).j - (*v).start + 2);
			if(!(*v).ret_buf)
			{
				free((*v).buffer);
				(*v).buffer = NULL;
				(*v).is_1_call = 1;
				return 0;
			}
			ft_strlcpy((*v).ret_buf, (*v).buffer + (*v).start, (*v).j - (*v).start + 2);
			(*v).is_1_call = 1;
			(*v).j++;
			return 0;
		}
		(*v).j++;
	}	
	return 1;
}


static char end_of_ln(t_vars *v)
{
	if(!(*v).read_ret && (*v).buffer[((*v).j - 1) * ((*v).j > 0)] != '\n' && (*v).j)
	{
		(*v).ret_buf = malloc((*v).j - (*v).start + 1);
		if(!(*v).ret_buf)
		{
			free((*v).buffer);
			(*v).buffer = NULL;
			(*v).is_1_call = 1;
			return 0;
		}
		ft_strlcpy((*v).ret_buf, (*v).buffer + (*v).start, (*v).j - (*v).start + 1);
		(*v).is_1_call = 1;
		(*v).j++;
		free((*v).buffer);
		(*v).buffer = NULL;
		return 0;
	}
	if(!(*v).j)
	{
		free((*v).buffer);
		(*v).buffer = NULL;
		return 0;
	}
	return 1;
}

static char handle_buffer_reading(t_vars *v, int fd)
{
	if((BUFFER_SIZE + 1000) >= ((*v).size - (*v).i))
	{
		(*v).buffer_swap = (*v).buffer;
		(*v).buffer = malloc(((*v).i + BUFFER_SIZE) * 4 + (*v).size );
		(*v).size = ((*v).i + BUFFER_SIZE) * 4 + (*v).size;
		if(!(*v).buffer)
		{
			free((*v).buffer_swap);
			return 0;
		}
		if((*v).buffer_swap)
		{
			ft_memcpy((*v).buffer, (*v).buffer_swap, (*v).size - ((*v).i + BUFFER_SIZE) * 4);
			free((*v).buffer_swap);
		}
		(*v).buffer_swap = NULL;
	}
	(*v).read_ret = read(fd, (*v).buffer + (*v).i, BUFFER_SIZE);
	(*v).i += (*v).read_ret;
	if((*v).read_ret == -1)
	{
		free((*v).buffer);
		(*v).buffer = NULL;
		(*v).is_1_call = 1;
		return 0;
	}
	return 1;
}

char *get_next_line(int fd)
{
	static t_vars vars;

	if(!gnl_init(&vars))
		return NULL;
	if(!vars.read_ret && vars.is_1_call)
		return NULL;
	vars.start = vars.j;
	while(((vars.read_ret) && vars.read_ret != -1 )|| !vars.is_1_call)
	{
		if(!is_nl(&vars))
			return vars.ret_buf;
		if(!handle_buffer_reading(&vars, fd))
			return (NULL);
		if(!is_nl(&vars))
			return vars.ret_buf;
		if(!end_of_ln(&vars))
			return vars.ret_buf;
	}	
 	if(vars.buffer)
 		free(vars.buffer);	
 	vars.buffer = NULL;
	vars.is_1_call = 1;
	return NULL;
}
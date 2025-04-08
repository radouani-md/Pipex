/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:54 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/08 15:06:13 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>


char	**md_split(char const *s, char c);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*md_strjoin(char *s1, char *s2);
char *is_accessable(char **path, char **cmd);

#endif
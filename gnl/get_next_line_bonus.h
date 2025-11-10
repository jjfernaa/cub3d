#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//-------------GET_NEXT_LINE.C----------------//
char	*get_next_line(int fd);
char	*gnl_strchr(const char *s, int c);
char	*gnl_read_txt(int fd, char *save);
char	*gnl_extract_line(char *save);
char	*gnl_the_rest(char *save);
//-------------GET_NEXT_LINE_UTILS.C----------------//
size_t	gnl_strlen(const char *str);
char	*gnl_strcpy(char *s1, const char *s2);
char	*gnl_strdup(const char *s);
size_t	gnl_strlcat(char *dst, const char *src, size_t dstsize);
char	*gnl_strjoin(char *str1, char *str2);

#endif
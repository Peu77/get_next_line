#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif

char *get_next_line(int fd) {
    static char *lineBuffer = NULL;

    char *buffer;
    int bytesRead = 0;
    int totalBytesRead = 0;
    char *new_line_pos;

    buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
    while ((new_line_pos = ft_strchr(lineBuffer + totalBytesRead, '\n')) == NULL) {
        totalBytesRead += bytesRead;
        bytesRead = read(fd, buffer, BUFFER_SIZE);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        if (lineBuffer == NULL)
            lineBuffer = ft_strndup(buffer, (size_t) bytesRead);
        else {
            char *temp = ft_strjoin(lineBuffer, buffer);
            free(lineBuffer);
            lineBuffer = temp;
        }
    }
    free(buffer);

    if (bytesRead == -1)
        return (NULL);

    if (bytesRead == 0 && lineBuffer == NULL)
        return (NULL);

    if (new_line_pos == NULL) {
        if (lineBuffer == NULL || *lineBuffer == '\0')
            return (NULL);
        char *line = ft_strndup(lineBuffer, (size_t) ft_strlen(lineBuffer));
        free(lineBuffer);
        lineBuffer = NULL;
        return (line);
    }

    char *line = ft_strndup(lineBuffer, new_line_pos - lineBuffer + 1);
    char *temp = ft_strndup(new_line_pos + 1, (size_t) ft_strlen(new_line_pos + 1));
    free(lineBuffer);
    lineBuffer = temp;
    return (line);
}

/*
int main() {
    char *line;
    int fd = open("../get_next_line.c", O_RDONLY);
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    close(fd);
    return (0);
}
 */
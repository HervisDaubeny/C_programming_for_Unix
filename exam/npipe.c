#define MALLOC(ptr, size) do {\
	ptr = malloc(size);\
	if(ptr == NULL) {\
		printf("malloc() error, NULL returned\n");\
		exit(1);\
	}\
}\
while(0)

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char* get_filename(int);
int get_data_length(int);
void read_to_tmp(int, int, const char*);
void write_reverse(char*, const char*);

int main(const int argc, char* argv[]) {
    char* my_fifo = argv[1];
    const char* temp_file = "/tmp/my_file";
    int out_fd;
    
    out_fd = open(temp_file, O_CREAT, 0777);
    close(out_fd);

    if (mkfifo(my_fifo, 0666) == -1)
    {
        if (errno != EEXIST) {
            printf("Error creating fifo. Errno: %d\n", errno);
        }
        //else everything's fine, fifo already exists
    }
    
    int fd = open(my_fifo, O_RDONLY);
    if (fd == -1)
    {
        printf("Something unexpected happend. Errno: %d\n", errno);
        exit(1);
    }
    
    while (1)
    {
        char* file = get_filename(fd);
        int length = get_data_length(fd);
        read_to_tmp(fd, length, temp_file);
        write_reverse(file, temp_file);
    }
    
    close(fd);
    return 0;
}

char* get_filename(int fd) {
    size_t max_size = 255;
    size_t red;
    int nl = 0;
    char c = '\0';
    char* filename;

    MALLOC(filename, max_size);
    
    for (size_t i = 0; i < max_size; i++)
    {
        red = read(fd, &c, 1);
        if (red == 0) {
            sleep(1);
        }
        
        if (c == '\n')
        {
            filename[i] = '\0';
            nl = 1;
            break;
        } else {
            filename[i] = c;
        }
    }
    
    if (nl == 0)
    {
        printf("Filename is longer than 255 chars. Exiting.");
        exit(1);
    }

    return filename;    
}

int get_data_length(int fd) {
    size_t max_size = 11;
    size_t red;
    int length;
    char c = '\0';
    char* buff;
    MALLOC(buff, max_size); // max_int will have <= 10 ciphers
    
    for (size_t i = 0; i < max_size; i++)
    {
        red = read(fd, &c, 1);
        if (red == 0) {
            sleep(1);
        }
        
        if (c == '\n')
        {
            buff[i] = '\0';
            break;
        } else {
            buff[i] = c;
        }
    }
    
    length = (int) strtol(buff, NULL, 10);
    
    return length;
}

void read_to_tmp(int fd, int lenght, const char* tmp) {
    size_t red;
    size_t buff_size = 4096;
    int progress = 0;
    char* buff;
    MALLOC(buff, buff_size);
    
    int out_fd = open(tmp, O_WRONLY);
    
    while(progress < lenght) {
        red = read(fd, buff, (size_t)lenght);
        if (red > 0)
        {
            if (write(out_fd, buff, red) == -1) {
                printf("Error writing to file. Errno: %d\n", errno);
                exit(1);
            }
        }
        
        progress += (int)red;
    }
    
    close(out_fd);
}

void write_reverse(char* out_file, const char* in_file) {
    int in;
    int out = open(out_file, O_CREAT, 0777);
    char c = '\0';
    size_t red;
    close(out);

    off_t current = 0;

    out = open(out_file, O_WRONLY);
    in = open(in_file, O_RDONLY);
    
    current = lseek(in, 0, SEEK_END);

    while (current >= 0) {
        red = read(in, &c, 1);
        current = lseek(in, current - 1, SEEK_SET);
        write(out, &c, 1);
    }
    
    close(in);
    close(out);
}
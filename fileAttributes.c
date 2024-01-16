#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

//#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buffer[50];
    int length;

    struct stat fileStat;
    int file = open("fileAttribute.txt", O_WRONLY | O_CREAT, 0777);
    if (file == -1)
    {
        write(2, "Error with the file", 20);
        return 1;
    }
    dup2(file, 1);
    close(file);
    int fd = STDOUT_FILENO;
    if (argc != 2)
    {
        length = sprintf(buffer, "usage: %s", argv[1]);
        write(fd, buffer, length);
    }
    const char *filePath = argv[1];
    char buffer2[1024];
    int length2= sprintf(buffer2, "%s", filePath);
    write(fd, "File attributes For: ", 22);
    write(fd, buffer2, length2);
    int length3= sprintf(buffer2, "File size: %ld bytes\n", fileStat.st_size);
    write(fd, buffer2, length3);
    //length2= sprintf(buffer2, "Hard link count: %ld\n", (long)fileStat.st_nlink);
    //write(fd, buffer2, length2);
    int length4 = sprintf(buffer2, "I-node number: %ld\n", (long)fileStat.st_ino);
    write(fd, buffer2, length4);
    int length5 = sprintf(buffer2, "Mode: %lo (octal)\n", (unsigned long)fileStat.st_mode);
    write(fd, buffer2, length5);

    int rev = open("fileAttribute.txt", O_RDONLY);
    if (rev == -1){
        return 2;
    }

    char buffer3[BUFFER_SIZE];
    ssize_t bytesRead;
    size_t totalBytesRead = 0;

    while ((bytesRead = read(rev, buffer3 + totalBytesRead, BUFFER_SIZE - totalBytesRead)) > 0){
        totalBytesRead += bytesRead;
    }
                                                                                                                       #include <stdio.h>

    if (bytesRead == -1){
        return 3;
    }

    for (size_t i = 0, j = totalBytesRead -1; i < j; ++i, --j){
        char temp = buffer3[i];
        buffer3[i] = buffer3[j];
        buffer3[j] = temp;
    }

    int revW = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (revW == -1){
        close(rev);
        return 4;
    }

    if (write(revW, buffer3, totalBytesRead) == -1){
        close(rev);
        close(revW);
        return 5;
    }

    close(rev);
    close(revW);


    //system("tac -r fileAttributes.txt > reverse.txt");

    return 0;
}
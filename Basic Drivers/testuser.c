#include<stdio.h>

#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_LENGTH 256 // The buffer length
static char receive[BUFFER_LENGTH]; // The receive buffer
int main() {
int ret, fd;
char stringToSend[BUFFER_LENGTH];
printf("Starting device test code example...\n");
fd = open("/dev/mydev1", O_RDWR); // Open the device with read/write access
if (fd< 0) {
perror("Failed to open the device...\n");
return errno;
}
printf("Type in a short string to send to the kernel module:\n");
scanf("%[^\n]c", stringToSend); // Read in a string (with spaces)
printf("Writing message to the device [%s].\n", stringToSend);
ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
if (ret < 0) {
perror("Failed to write the message to the device.\n");
return errno;
}
printf("Press ENTER key to read back from the device...\n");
getchar();
printf("Reading from the device...\n");
unsigned int len = 0;
unsigned int offset = 0;
len = pread(fd, receive, BUFFER_LENGTH, offset);
printf("Offset : %ul\n", offset);
// ret = read(fd, receive, BUFFER_LENGTH); // Read the response from the LKM
if (len< 0) {
perror("Failed to read the message from the device.\n");
return errno;
}
printf("Read data of length: %ul\n", len);
printf("The received message is: [%s]\n", receive);
printf("End of the program\n");
return 0;
}

#include <stdio.h>
#include <unistd.h>

#define HERE_DOC_NAME "here_doc.txt"

int main() {
    if (unlink(HERE_DOC_NAME) == -1) {
        perror("Error deleting the file");
    } else {
        printf("File deleted successfully\n");
    }
    return 0;
}
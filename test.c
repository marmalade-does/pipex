#include <stdio.h>
#include <unistd.h>

int main() {
    if (unlink("myfile.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }
    return 0;
}

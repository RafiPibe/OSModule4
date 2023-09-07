#include <stdio.h>
#include <stdlib.h>

void downloadExtract() {
    char command[500];
    // sprintf(command, "wget \"https://drive.google.com/u/0/uc?id=18YCFdG658SALaboVJUHQIqeamcfNY39a&export=download\" -O rahasia.zip");
    sprintf(command, "wget --no-check-certificate \'https://drive.google.com/uc?export=download&id=18YCFdG658SALaboVJUHQIqeamcfNY39a&confirm=t&uuid=38b0d9df-d8cc-46c8-9f03-b455b6f12ed9&at=AKKF8vzt0K3vcrmKQYVrFdCQpjzY:1685177895570\' -O rahasia.zip");

    int status = system(command);
    if(status == -1) {
        printf("Failed to download.\n");
    }

    char command2[100];
    sprintf(command2, "unzip rahasia.zip");

    status = system(command2);
    if(status == -1) {
        printf("Failed to extract\n");
    }
}

int main() {
    downloadExtract();
    return 0;
}

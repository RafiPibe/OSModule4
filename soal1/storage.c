#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void downloadFile() {
    // Initialize chars
    const char* downloadData = "kaggle datasets download -d bryanb/fifa-player-stats-database";
    const char* extractData = "unzip fifa-player-stats-database.zip";
    const char* removeZip = "rm fifa-player-stats-database.zip";
    
    // execute system
    system(downloadData);
    system(extractData);
    system(removeZip);
}

void processFile(const char* filename) {
    FILE *fpt;
    char str[500];
    char* token;
    int age, potential;
    char* club;
    char* name;
    char* photo;
    int i;

    fpt = fopen(filename,"r");

    if(fpt == NULL) {
        printf("Can't open file %s\n", filename);
        exit(1);
    } else {
        while(fgets(str,500,fpt)) {
            i = 1;  // Reset counter for each line
            token = strtok(str, ",");
            while(token != NULL) {
                if(i == 2) {  // 2nd field is name
                    name = token;
                } else if(i == 3) {  // 3rd field is age
                    age = atoi(token);
                } else if(i == 4) {  // 4th field is photo
                    photo = token;
                } else if(i == 8) {  // 8th field is potential
                    potential = atoi(token);
                } else if(i == 9) {  // 9th field is club
                    club = token;
                }
                token = strtok(NULL, ",");
                i++;  // Increment field counter
            }
            // Check conditions
            if(age < 25 && potential > 85 && strcmp(club, "Manchester City") != 0) {
                printf("Name: %s\nAge: %d\nPhoto: %s\nPotential: %d\nClub: %s\n\n", name, age, photo, potential, club);
            }
        }
        fclose(fpt);
    }
}

int main() {
    const char* filename = "FIFA23_official_data.csv";

    downloadFile();
    processFile(filename);
    return 0;
}

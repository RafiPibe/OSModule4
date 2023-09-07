 # <b><i>sisop-praktikum-modul-03-2023-IF184402-UO4</i></b>

## Group UO4

This is our attempt on the 4th Practicum of Operation System 
consisting the members as following:

| Name                        | NRP        |
|-----------------------------|------------|
|Hanifi Abrar Setiawan        | 5025211066 |
|Faraihan Rafi Adityawarman   | 5025211074 |
|Vija Wildan Gita Prabawa     | 5025211261 |

## <b>1st Problem</b>

Kota Manchester sedang dilanda berita bahwa kota ini mau juara (yang kota ‘loh ya, bukan yang satunya). Tagline #YBBA (#YangBiruBiruAja #anjaykelaspepnihbossenggoldong 💪🤖🤙🔵⚪) sudah mewabah di seluruh dunia. Semua warga pun sudah menyiapkan pesta besar-besaran. 
Seorang pelatih sepak bola handal bernama Peb merupakan pelatih klub Manchester Blue, sedang berjuang memenangkan Treble Winner. Untuk meraihnya, ia perlu melakukan pembelian pemain dengan ideal. Agar sukses, ia memahami setiap detail data performa pemain sepak bola seluruh dunia yang meliputi statistik pemain, umur, tinggi dan berat badan, potensi, klub dan negaranya, serta banyak data lainnya. Namun, tantangan tersendiri muncul ketika mengelola dan mengakses data berukuran besar ini.
Kesulitan Peb tersebut mencapai telinga kalian, seorang mahasiswa Teknik Informatika yang ahli dalam pengolahan data. Mengetahui tantangan Peb, kalian diminta untuk membantu menyelesaikan masalahnya melalui beberapa langkah berikut.

### Explanation

```c
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
```
This function is used to download the csv file, extract it, then removing the zip to clear the storage.

```c
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
    ...
}
```
initializing everything

```c
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
            ...
        }
    }
```

this is to search inside the csv, like to see the 2nd field is the name, 3rd field age, etc.

```c
// Check conditions
            if(age < 25 && potential > 85 && strcmp(club, "Manchester City") != 0) {
                printf("Name: %s\nAge: %d\nPhoto: %s\nPotential: %d\nClub: %s\n\n", name, age, photo, potential, club);
            }
```

now using this if statement to filter out the one that have the age below 25, and potential above 85, also a club other than manchester city.

```dockerfile
# Set the base image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Copy the necessary files to the container
COPY FIFA23_official_data.csv /app
COPY storage.c /app

# Install dependencies and set up the environment
RUN apt-get update && \
    apt-get install -y gcc

# Define the command to compile and run the C program
CMD gcc -o storage storage.c && ./storage
```

save this dockerfile, then run the command in terminal below:
```
// building the image
docker build -t storage-app .

// tagging the image
docker tag storage-app faraihanrafia/storage-app:ybba

// pushing the image
docker login // inserting credentials
docker push faraihanrafia/storage-app:ybba
```
then after that we can see the tag in the web :  https://hub.docker.com/r/faraihanrafia/storage-app.

```yml
version: '3'
services:
  barcelona:
    build:
      context: /home/pibe/Sisop4/Barcelona/
      dockerfile: Dockerfile
    deploy:
      replicas: 5
  napoli:
    build:
      context: /home/pibe/Sisop4/Napoli/
      dockerfile: Dockerfile
    deploy:
      replicas: 5
```
the services are provided 9(barcelona and napoli), inside both services, there's the directories and the file of dockerfile, then we deploy them with 5 replicas each.
run the yml file with commands below in terminal

```cmd
docker-compose up -d
```

## <b>2nd Problem</b>

Nana adalah peri kucing yang terampil dalam menggunakan sihir, dia bisa membuat orang lain berubah menjadi Molina. Suatu hari, dia bosan menggunakan sihir dan mencoba untuk magang di germa.dev sebagai programmer.
Agar dapat diterima sebagai karyawan magang dia diberi sebuah file .zip yang berisi folder dan file dari Germa. Kemudian, Nana harus membuat sistem manajemen folder dengan ketentuan sebagai berikut:
Apabila terdapat file yang mengandung kata restricted, maka file tersebut tidak dapat di-rename ataupun dihapus.
Apabila terdapat folder yang mengandung kata restricted, maka folder tersebut, folder yang ada di dalamnya, dan file yang ada di dalamnya tidak dapat di-rename ataupun dihapus.

```c
#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

// Lokasi folder terbatas (restricted)
const char *restricted_folder = "/home/nipi/nanaxgerma/src_data/germaa/";

// Fungsi untuk memeriksa apakah path mengandung kata restricted
int is_restricted(const char *path) {
    return strstr(path, "restricted") != NULL;
}
```
is_restricted(const char *path): Fungsi ini memeriksa apakah suatu path mengandung kata "restricted". Fungsi ini digunakan untuk memvalidasi apakah path yang diberikan merupakan path ke folder yang terbatas (restricted).

```c
static int germa_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    char fpath[4096]; // Menggunakan nilai konstan

    sprintf(fpath, "%s%s", restricted_folder, path);

    res = lstat(fpath, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}
```
germa_getattr(const char *path, struct stat *stbuf): Fungsi ini digunakan untuk mendapatkan atribut (metadata) dari suatu file atau direktori. Fungsi ini menerima path dari file/direktori yang diminta dan pointer ke struktur struct stat yang akan diisi dengan informasi atribut.

```c
static int germa_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    DIR *dp;
    struct dirent *de;

    (void)offset;
    (void)fi;

    char fpath[4096]; // Menggunakan nilai konstan

    sprintf(fpath, "%s%s", restricted_folder, path);

    dp = opendir(fpath);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL)
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;

        if (filler(buf, de->d_name, &st, 0))
            break;
    }

    closedir(dp);
    return 0;
}
```
germa_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi): Fungsi ini digunakan untuk membaca isi dari suatu direktori. Fungsi ini menerima path dari direktori yang diminta, buffer yang akan diisi dengan entri-entri direktori, pointer ke fungsi filler yang akan digunakan untuk mengisi entri-entri direktori ke buffer, offset, dan pointer ke struct fuse_file_info.

```c
static int germa_mkdir(const char *path, mode_t mode)
{
    int res = 0;
    char fpath[4096]; // Menggunakan nilai konstan

    sprintf(fpath, "%s%s", restricted_folder, path);

    if (is_restricted(fpath))
        return -EPERM;

    res = mkdir(fpath, mode);
    if (res == -1)
        return -errno;

    return 0;
}
```
germa_mkdir(const char *path, mode_t mode): Fungsi ini digunakan untuk membuat direktori baru. Fungsi ini menerima path dari direktori yang akan dibuat dan mode akses yang akan diberikan kepada direktori tersebut.

```c
static int germa_rename(const char *from, const char *to)
{
    int res = 0;
    char fpath_from[4096]; // Menggunakan nilai konstan
    char fpath_to[4096];   // Menggunakan nilai konstan

    sprintf(fpath_from, "%s%s", restricted_folder, from);
    sprintf(fpath_to, "%s%s", restricted_folder, to);

    if (is_restricted(fpath_from) || is_restricted(fpath_to))
        return -EPERM;

    res = rename(fpath_from, fpath_to);
    if (res == -1)
        return -errno;

    return 0;
}
```
germa_rename(const char *from, const char *to): Fungsi ini digunakan untuk mengubah nama sebuah file atau direktori. Fungsi ini menerima path asal (from) dan path tujuan (to) dari file/direktori yang akan diubah Namanya.

```c
static int germa_unlink(const char *path)
{
    int res = 0;
    char fpath[4096]; // Menggunakan nilai konstan

    sprintf(fpath, "%s%s", restricted_folder, path);

    if (is_restricted(fpath))
        return -EPERM;

    res = unlink(fpath);
    if (res == -1)
        return -errno;

    return 0;
}
```
germa_unlink(const char *path): Fungsi ini digunakan untuk menghapus (meng-unlink) sebuah file. Fungsi ini menerima path dari file yang akan dihapus.

```c
static int germa_rmdir(const char *path)
{
    int res = 0;
    char fpath[4096]; // Menggunakan nilai konstan

    sprintf(fpath, "%s%s", restricted_folder, path);

    if (is_restricted(fpath))
        return -EPERM;

    res = rmdir(fpath);
    if (res == -1)
        return -errno;

    return 0;
}
```
germa_rmdir(const char *path): Fungsi ini digunakan untuk menghapus sebuah direktori. Fungsi ini menerima path dari direktori yang akan dihapus.

```c
static int germa_rename_restricted_folder()
{
    char restricted_list_path[4096];
    char bypass_list_path[4096];
    char projectMagang_path[4096];

    sprintf(restricted_list_path, "%sprojects/restricted_list", restricted_folder);
    sprintf(bypass_list_path, "%sprojects/bypass_list", restricted_folder);
    sprintf(projectMagang_path, "%sprojects/bypass_list/projectMagang", restricted_folder);

    // Mengubah nama folder restricted_list menjadi bypass_list
    if (rename(restricted_list_path, bypass_list_path) == -1)
        return -errno;

    // Membuat folder projectMagang di dalam bypass_list
    if (mkdir(projectMagang_path, 0777) == -1)
        return -errno;

    return 0;
}
```
germa_rename_restricted_folder(): Fungsi ini digunakan untuk mengubah nama folder "restricted_list" menjadi "bypass_list" dan membuat folder "projectMagang" di dalamnya. Fungsi ini akan dipanggil pada saat program utama dijalankan.

```c
static int germa_rename_filePenting()
{
    char filePenting_path[4096];
    char restrictedFilePenting_path[4096];

    sprintf(filePenting_path, "%sprojects/filePenting", restricted_folder);
    sprintf(restrictedFilePenting_path, "%sprojects/restrictedFilePenting", restricted_folder);

    // Mengubah nama folder filePenting menjadi restrictedFilePenting
    if (rename(filePenting_path, restrictedFilePenting_path) == -1)
        return -errno;

    return 0;
}
```
Germa_rename_filepenting (): Fungsi ini digunakan untuk mengubah nama folder “FilePenting” menjadi “restrictedFilePenting”.

```c
static struct fuse_operations germa_oper = {
    .getattr = germa_getattr,
    .readdir = germa_readdir,
    .mkdir = germa_mkdir,
    .rename = germa_rename,
    .unlink = germa_unlink,
    .rmdir = germa_rmdir,
};

int main(int argc, char *argv[])
{
    umask(0);

    if (germa_rename_restricted_folder() == -1)
    {
        fprintf(stderr, "Error: Failed to rename restricted_list folder or create projectMagang folder.\n");
        return 1;
    }

    if (germa_rename_filePenting() == -1)
    {
        fprintf(stderr, "Error: Failed to rename filePenting folder.\n");
        return 1;
    }

    return fuse_main(argc, argv, &germa_oper, NULL);
}

```
main(int argc, char *argv[]): Fungsi utama program. Fungsi ini menjalankan logika utama dari program FUSE. Di dalam fungsi ini, mode umask diatur menjadi 0, dan kemudian fungsi germa_rename_restricted_folder() dipanggil untuk mengubah nama folder dan membuat folder baru. Setelah itu, fungsi fuse_main() dipanggil untuk menjalankan FUSE dengan menggunakan operasi-operasi yang telah didefinisikan sebelumnya.


## <b>5th Problem</b>

Setelah sukses menjadi pengusaha streaming musik di chapter kehidupan sebelumnya, Elshe direkrut oleh lembaga rahasia untuk membuat sistem rahasia yang terenkripsi.  Kalian perlu membantu Elshe dan membuat program rahasia.c. Pada program rahasia.c, terdapat beberapa hal yang harus kalian lakukan sebagai berikut.					


#### A
Program rahasia.c merupakan file FUSE yang akan digunakan untuk melakukan mount folder pada Docker Container. Unduh file rahasia.zip kemudian lakukan unzip pada file rahasia.zip menjadi folder rahasia.

#### Answer

```c
#include <stdio.h>
#include <stdlib.h>

void downloadExtract() {
    char command[500];
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

```

#### Explanation

The code includes standard libraries for input/output operations and memory allocation. It defines a function called `downloadExtract()` that downloads a file from a specific URL and extracts its contents. Inside the function, a command string is declared to store the system command. The `sprintf` function is used to format the command, creating a `wget` command to download a file from a Google Drive link and save it as "rahasia.zip". The `system()` function is then called to execute the command, and the return value is checked for any errors. Another command string is created using `sprintf`, this time constructing an unzip command to extract the contents of the downloaded ZIP file. The `system()` function is called again to execute this extraction command, and the return value is checked for errors. In the `main()` function, `downloadExtract()` is called to initiate the download and extraction process. Finally, the program returns 0 to indicate successful execution. It should be noted that the code assumes the availability of the `wget` and `unzip` commands in the system's command shell, and the provided Google Drive link should be verified and adjusted as needed.

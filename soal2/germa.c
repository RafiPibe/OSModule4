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

// Fungsi untuk mengubah nama folder restricted_list menjadi bypass_list dan membuat folder projectMagang di dalamnya
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

// Fungsi untuk mengubah nama folder filePenting menjadi restrictedFilePenting
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

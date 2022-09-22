//
// Created by mxlei on 2022/9/11.
//

#include "file_patcher.h"
#include <bzlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "bspatch.h"
#include <android/log.h>


#ifdef __cplusplus
extern "C" {
#endif

static int64_t offtin(uint8_t *buf) {
    int64_t y;
    y = buf[7] & 0x7F;
    y = y * 256;
    y += buf[6];
    y = y * 256;
    y += buf[5];
    y = y * 256;
    y += buf[4];
    y = y * 256;
    y += buf[3];
    y = y * 256;
    y += buf[2];
    y = y * 256;
    y += buf[1];
    y = y * 256;
    y += buf[0];
    if (buf[7] & 0x80) y = -y;
    return y;
}

static int bz2_read(const struct bspatch_stream *stream, void *buffer, int length) {
    int n;
    int bz2err;
    BZFILE *bz2;

    bz2 = (BZFILE *) stream->opaque;
    n = BZ2_bzRead(&bz2err, bz2, buffer, length);
    if (n != length)
        return -1;

    return 0;
}

int bspatch_file(const char *old_file, const char *new_file, const char *patch_file) {
    FILE *f;
    int fd;
    int bz2err;
    uint8_t header[24];
    uint8_t *old, *new;
    int64_t oldsize, newsize;
    BZFILE *bz2;
    struct bspatch_stream stream;
    struct stat sb;

    int argc = 4;
    const char *argv[4];
    argv[0] = "";
    argv[1] = old_file;
    argv[2] = new_file;
    argv[3] = patch_file;
    if (argc != 4) errx(1, "usage: %s oldfile newfile patchfile\n", argv[0]);

    /* Open patch file */
    if ((f = fopen(argv[3], "r")) == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error open oldfile %s\n", old_file);
        return -1;
    }

    /* Read header */
    if (fread(header, 1, 24, f) != 24) {
        if (feof(f))
            errx(1, "Corrupt patch\n");
        err(1, "fread(%s)", argv[3]);
    }

    /* Check for appropriate magic */
    if (memcmp(header, "ENDSLEY/BSDIFF43", 16) != 0)
        errx(1, "Corrupt patch\n");

    /* Read lengths from header */
    newsize = offtin(header + 16);
    if (newsize < 0)
        errx(1, "Corrupt patch\n");

    /* Close patch file and re-open it via libbzip2 at the right places */
    if (((fd = open(argv[1], O_RDONLY, 0)) < 0) ||
        ((oldsize = lseek(fd, 0, SEEK_END)) == -1) ||
        ((old = malloc(oldsize + 1)) == NULL) ||
        (lseek(fd, 0, SEEK_SET) != 0) ||
        (read(fd, old, oldsize) != oldsize) ||
        (fstat(fd, &sb)) ||
        (close(fd) == -1)) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error read oldfile %s\n", old_file);
        return -1;
    }
    if ((new = malloc(newsize + 1)) == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error malloc memory %lld\n",
                            newsize + 1);
        return -1;
    }

    if (NULL == (bz2 = BZ2_bzReadOpen(&bz2err, f, 0, 0, NULL, 0))) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error bzReadOpen\n");
        return -1;
    }


    stream.read = bz2_read;
    stream.opaque = bz2;
    if (bspatch(old, oldsize, new, newsize, &stream)) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error execute bspatch\n");
        return -1;
    }

    /* Clean up the bzip2 reads */
    BZ2_bzReadClose(&bz2err, bz2);
    fclose(f);

    /* Write the new file */
    if (((fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, sb.st_mode)) < 0) ||
        (write(fd, new, newsize) != newsize) || (close(fd) == -1)) {
        __android_log_print(ANDROID_LOG_ERROR, "bspatch", "error write new file %s\n", new_file);
        return -1;
    }

    free(new);
    free(old);
    return 0;
}

#ifdef __cplusplus
};
#endif
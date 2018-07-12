#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
// #include <fcntl.h>


// ret: -1: error, see ERRNO
//      0 : success
static int makedir(const char *dir, mode_t mode)
{
	struct stat st;
	int ret = -1;

	if (dir == NULL) {
		return ret;
	}

	size_t sz = strlen(dir);
	if (sz == 0)
	{
		return ret;
	}
	assert(sz < PATH_MAX);

	char buf[PATH_MAX];
	strncpy(buf, dir, sz);
	buf[PATH_MAX - 1] = '\0';

	if (buf[sz - 1] == '/') {
		buf[sz - 1] = '\0';
	}

	if (strlen(buf) == 0) {
		// this is a root dir ("/")
		return 0;
	}

	if (stat(buf, &st)) {
		return mkdir(buf, mode);
	}

	if (!S_ISDIR(st.st_mode)) {
		if (unlink(buf)) {
			return -1;
		}
		return mkdir(buf, mode);
	}
	return 0;
}

static int makedir_p(const char *dir, mode_t mode)
{
	if (makedir(dir, mode) == 0) {
		return 0;
	}

	size_t sz = strlen(dir);
	if (sz == 0)
	{
		return -1;
	}
	assert(sz < PATH_MAX);

	char buf[PATH_MAX];
	strncpy(buf, dir, sz);
	buf[PATH_MAX - 1] = '\0';

	if (buf[sz - 1] == '/') {
		buf[sz - 1] = '\0';
	}

	char *off = strrchr(buf, '/');
	if (off != NULL) {
		// recursion
		*off = '\0';
		makedir_p(buf, mode);
		*off = '/';
		return makedir(dir, mode);
	}

	return -1;
}

#ifdef MKDIR_TEST

#include <errno.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        printf("input dest path to mkdir\n");
        return -1;
    }
    for (int i = 1; i < argc; i++) {
        int ret = makedir_p(argv[i], 0777);
        printf("mkdir(%s) -> %d\n", argv[i], ret);
        if (ret == -1) {
            printf("errno : %d\n", errno);
        }
    }
    return 0;
}
#endif /* MKDIR_TEST */
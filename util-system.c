#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util-system.h"
#include "util-string.h"

#define PASSWD_FILE         "/etc/passwd"
#define PASSWD_FILE_COLUMN  7

#ifdef SYSTEM_MAIN
#define PRINT(fmt, arg...)      printf("[%s] " fmt, __func__, ##arg)
#else
#define PRINT(fmt, arg...)      
#endif 

static int get_file_lines(const char *fname)
{
    FILE *file = fopen(fname, "r");
    int total = 0;
    if(file) {
        int c;
        while(EOF != (c = fgetc(file)))
            if('\n' == c)
                total++; 
    }
    return total;
}

void users_free(users_info_t *users)
{
    if(!users)
        return;
    int index = 0;
    for(index=0; index<users->total; index++) {
        free(users->user[index].logname);
        free(users->user[index].passwd);
        free(users->user[index].name);
        free(users->user[index].home);
        free(users->user[index].shell);
    }
    free(users);
}

static int get_users_impl(users_info_t *users)
{
    FILE *file = fopen(PASSWD_FILE, "r");
    if(!file) {
        PRINT("open %s failed\n", PASSWD_FILE);
        return -1;
    }
    char line[4096];
    users->total = 0;
    while(NULL != fgets(line, sizeof(line), file))
    {
        char *start = strip(line);
        char **toks;
        int num_toks = 0;
        toks = mSplit(start, ":", PASSWD_FILE_COLUMN, &num_toks, 0);
        if(PASSWD_FILE_COLUMN != num_toks) {
            mSplitFree(&toks, num_toks);
            continue;
        }
        if(NULL != strchr(toks[4], ','))
            *strchr(toks[4], ',') = '\0';
        users->user[users->total].logname  = strdup(toks[0]);
        users->user[users->total].passwd = strdup(toks[1]);
        users->user[users->total].uid      = atoi(toks[2]);
        users->user[users->total].gid      = atoi(toks[3]);
        users->user[users->total].name     = strdup(toks[4]);
        users->user[users->total].home     = strdup(toks[5]);
        users->user[users->total].shell    = strdup(toks[6]);
        mSplitFree(&toks, num_toks);
        users->total++;
    }
    return 0;
}

users_info_t *get_users()
{
    int n_users = get_file_lines(PASSWD_FILE);
    if(0 == n_users)
        return NULL;
    users_info_t *users = (users_info_t *)malloc(sizeof(users_info_t) + n_users * sizeof(user_info_t));
    if(users) {
        if(0 == get_users_impl(users)) {
            return users;
        }
        else {
            users_free(users);
        }
    }
    return NULL;
}

void users_print(users_info_t *users)
{
    if(!users)
        return;
    int index = 0;
    for(index=0; index<users->total; index++) {
        printf("%s :\n", users->user[index].name);
        printf("\tlogname: %s\n", users->user[index].logname);
        printf("\tpasswd : %s\n", users->user[index].passwd);
        printf("\tuid    : %d\n", users->user[index].uid);
        printf("\tgid    : %d\n", users->user[index].gid);
        printf("\tname   : %s\n", users->user[index].name);
        printf("\thome   : %s\n", users->user[index].home);
        printf("\tshell  : %s\n", users->user[index].shell);
    }
}

char *get_user_name_by_uid(users_info_t *users, int uid)
{
    int index = 0;
    for(index=0; index < users->total; index++) {
        if(users->user[index].uid == uid)
            return users->user[index].logname;
    }
    return NULL;
}

#ifdef SYSTEM_MAIN
int main(int argc, char const *argv[])
{
    users_info_t *users = get_users();
    users_print(users);
    char *name = get_user_name_by_uid(users, 1000);
    PRINT("get_user_name_by_uid(%d) --> %s\n", 1000, name);
    users_free(users);
    return 0;
}
#endif

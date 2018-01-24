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

static int user_passwd_prepare_alloc(users_passwd_t *users)
{
    if(users->capacity == users->used) {
        size_t capacity = users->capacity * 5 / 4 + 1;
        user_passwd_t *ptr = (user_passwd_t *)realloc(users->users, capacity * sizeof(user_passwd_t));
        if(!ptr) {
            return -1;
        }
        memset(ptr + users->capacity, 0, (capacity - users->capacity) * sizeof(user_passwd_t));
        users->users = ptr;
        users->capacity = capacity;
    }
    return 0;
}

void users_passwd_free(users_passwd_t *users)
{
    if(users) {
        if(users->users) {
            int index = 0;
            for(index=0; index<users->used; index++) {
                free(users->users[index].logname);
                free(users->users[index].passwd);
                free(users->users[index].name);
                free(users->users[index].home);
                free(users->users[index].shell);
            }
            free(users->users);
        }
        free(users);
    }
}

static int get_users_passwd_impl(users_passwd_t *users)
{
    FILE *file = fopen(PASSWD_FILE, "r");
    if(!file) {
        PRINT("open %s failed\n", PASSWD_FILE);
        return -1;
    }
    char line[4096];
    users->used = 0;
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
        if(user_passwd_prepare_alloc(users) < 0)
            continue;
        if(NULL != strchr(toks[4], ','))
            *strchr(toks[4], ',') = '\0';
        users->users[users->used].logname  = strdup(toks[0]);
        users->users[users->used].passwd = strdup(toks[1]);
        users->users[users->used].uid      = atoi(toks[2]);
        users->users[users->used].gid      = atoi(toks[3]);
        users->users[users->used].name     = strdup(toks[4]);
        users->users[users->used].home     = strdup(toks[5]);
        users->users[users->used].shell    = strdup(toks[6]);
        mSplitFree(&toks, num_toks);
        users->used++;
    }
    return 0;
}

users_passwd_t *get_users_passwd()
{
    users_passwd_t *users = (users_passwd_t *)calloc(1, sizeof(users_passwd_t));
    if(!users)
        return NULL;
    if(0 == get_users_passwd_impl(users)) {
        return users;
    }
    else {
        users_passwd_free(users);
    }
    return NULL;
}

void users_passwd_print(users_passwd_t *users)
{
    if(!users)
        return;
    printf("[%s] print all users in /etc/passwd :\n", __func__);
    int index = 0;
    for(index=0; index<users->used; index++) {
        printf("%s :\n", users->users[index].name);
        printf("\tlogname: %s\n", users->users[index].logname);
        printf("\tpasswd : %s\n", users->users[index].passwd);
        printf("\tuid    : %d\n", users->users[index].uid);
        printf("\tgid    : %d\n", users->users[index].gid);
        printf("\tname   : %s\n", users->users[index].name);
        printf("\thome   : %s\n", users->users[index].home);
        printf("\tshell  : %s\n", users->users[index].shell);
    }
}

char *get_user_name_by_uid(users_passwd_t *users, int uid)
{
    int index = 0;
    for(index=0; index < users->used; index++) {
        if(users->users[index].uid == uid)
            return users->users[index].logname;
    }
    return NULL;
}

#if 1
// /var/run/utmp  --  database of currently logged-in users
// /var/log/wtmp  --  database of past user logins

// /usr/include/bits/utmp.h --> struct utmp
// The structure describing the status of a terminated process. 
// This type is used in `struct utmp' below.

// struct exit_status
// {
//     short int e_termination;  // Process termination status.
//     short int e_exit;         // Process exit status.
// };

// The structure describing an entry in the user accounting database.
// struct utmp
// {
//   short int ut_type;          // Type of login.
//   pid_t ut_pid;               // Process ID of login process.
//   char ut_line[UT_LINESIZE];  // Devicename.
//   char ut_id[4];              // Inittab ID.
//   char ut_user[UT_NAMESIZE];  // Username.
//   char ut_host[UT_HOSTSIZE];  // Hostname for remote login.
//   struct exit_status ut_exit; // Exit status of a process marked as DEAD_PROCESS.

//   The ut_session and ut_tv fields must be the same size when compiled 32 && 64 bit.
//   This allows data files and shared memory to be shared between 32 && 64-bit applications.

// #if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
//   int32_t ut_session;         // Session ID, used for windowing.
//   struct
//   {
//     int32_t tv_sec;           // Seconds.
//     int32_t tv_usec;          // Microseconds.
//   } ut_tv;                    // Time entry was made.
// #else
//   long int ut_session;        // Session ID, used for windowing.
//   struct timeval ut_tv;       // Time entry was made.
// #endif

//   int32_t ut_addr_v6[4];      // Internet address of remote host.
//   char __unused[20];          // Reserved for future use.
// };

// // Values for the `ut_type' field of a `struct utmp'. 
// #define EMPTY           0       // No valid user accounting information.
// #define RUN_LVL         1       // The system's runlevel.
// #define BOOT_TIME       2       // Time of system boot. 
// #define NEW_TIME        3       // Time after system clock changed. 
// #define OLD_TIME        4       // Time when system clock changed. 
// #define INIT_PROCESS    5       // Process spawned by the init process. 
// #define LOGIN_PROCESS   6       // Session leader of a logged in user. 
// #define USER_PROCESS    7       // Normal process. 
// #define DEAD_PROCESS    8       // Terminated process. 
// #define ACCOUNTING      9


#include <utmp.h>

static user_utmp_t *get_user_by_name(users_utmp_t *users, const char *name)
{
    if(!users || !users->users)
        return NULL;
    int index = 0;
    for(index=0; index<users->used; index++) {
        if(0 == strcmp(users->users[index].name, name))
            return &users->users[index];
    }
    return NULL;
}

void users_utmp_free(users_utmp_t *users)
{
    if(users) {
        if(users->users) {
            int index = 0;
            for(index=0; index<users->used; index++) {
                free(users->users[index].name);
            }
            free(users->users);
        }
        free(users);
    }
}

static int user_utmp_prepare_alloc(users_utmp_t *users)
{
    if(users->capacity == users->used) {
        size_t capacity = users->capacity * 5 / 4 + 1;
        user_utmp_t *ptr = (user_utmp_t *)realloc(users->users, capacity * sizeof(user_utmp_t));
        if(!ptr) {
            return -1;
        }
        memset(ptr + users->capacity, 0, (capacity - users->capacity) * sizeof(user_utmp_t));
        users->users = ptr;
        users->capacity = capacity;
    }
    return 0;
}

static int get_users_utmp_impl(users_utmp_t *users)
{
#ifndef __linux__
    return -1;
#endif
    const char *path = NULL;
    // /usr/include/paths.h --> #define _PATH_UTMP "/var/run/utmp"
    path = _PATH_UTMP;
    FILE *file = fopen(path, "r");
    if(!file) {
        printf("%s open failed\n", path);
        return -1;
    }
    struct utmp usr;
    while (fread((char *)&usr, sizeof(usr), 1, file) == 1) {
        if (*usr.ut_name && *usr.ut_line && *usr.ut_line != '~') {
            if(get_user_by_name(users, usr.ut_name))
                continue;
            if(user_utmp_prepare_alloc(users) < 0)
                continue;
            PRINT("%s\n", usr.ut_name);
            users->users[users->used].name = strdup(usr.ut_name);
            users->used++;
        }
    }
    fclose(file);
    return 0;
}

users_utmp_t *get_users_utmp()
{
    users_utmp_t *users = (users_utmp_t *)calloc(1, sizeof(users_utmp_t));
    if(!users)
        return NULL;
    if(0 == get_users_utmp_impl(users)) {
        return users;
    }
    else {
        users_utmp_free(users);
    }
    return NULL;
}

void users_utmp_print(users_utmp_t *users)
{
    if(!users)
        return;
    int index = 0;
    printf("[%s] print currently logged-in users:\n", __func__);
    for(index=0; index<users->used; index++) {
        printf("%s,", users->users[index].name);
    }
    printf("\b \n");
}

#endif

#ifdef SYSTEM_MAIN
int main(int argc, char const *argv[])
{
    users_passwd_t *p_users_passwd = get_users_passwd();
    users_passwd_print(p_users_passwd);
    char *name = get_user_name_by_uid(p_users_passwd, 1000);
    PRINT("get_user_name_by_uid(%d) --> %s\n", 1000, name);
    users_passwd_free(p_users_passwd);

    users_utmp_t *p_users_utmp = get_users_utmp();
    users_utmp_print(p_users_utmp);
    users_utmp_free(p_users_utmp);
    return 0;
}
#endif

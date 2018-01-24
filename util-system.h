#ifndef __UTIL_SYSTEM_H__
#define __UTIL_SYSTEM_H__

typedef struct {
    char *logname;  // name when log in
    char *passwd;   // password, usually is 'x'.
    int uid;        // user id
    int gid;        // group id
    char *name;     // detail name, usually same as logname
    char *home;     // home directory
    char *shell;    // default shell
} user_passwd_t;

typedef struct {
    size_t        capacity;
    size_t        used;
    user_passwd_t *users;
} users_passwd_t;

// get from /etc/passwd
void users_passwd_free(users_passwd_t *users);
void users_passwd_print(users_passwd_t *users);
users_passwd_t *get_users_passwd();


char *get_user_name_by_uid(users_passwd_t *users, int uid);


typedef struct {
    char *name;
} user_utmp_t;

typedef struct {
    int capacity;
    int used;
    user_utmp_t *users;
} users_utmp_t;

void users_utmp_free(users_utmp_t *users);
void users_utmp_print(users_utmp_t *users);
users_utmp_t *get_users_utmp();

#endif // __UTIL_SYSTEM_H__

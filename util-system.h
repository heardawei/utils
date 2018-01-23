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
} user_info_t;

typedef struct {
    int         total;
    user_info_t user[0];
} users_info_t;

void users_free(users_info_t *users);
void users_print(users_info_t *users);
users_info_t *get_users();
char *get_user_name_by_uid(users_info_t *users, int uid);


#endif // __UTIL_SYSTEM_H__

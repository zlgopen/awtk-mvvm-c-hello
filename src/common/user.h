
#ifndef TK_USER_H
#define TK_USER_H

#include "tkc/str.h"
#include "tkc/mem.h"
#include "tkc/utils.h"

BEGIN_C_DECLS

/**
 * @class user_t
 *
 * user info
 */
typedef struct _user_t {
  str_t name;
  str_t nick_name;
  str_t password;
  time_t registered_time;
  time_t last_login_time;
} user_t;

static inline user_t* user_create(void) {
  user_t* user = TKMEM_ZALLOC(user_t);
  return_value_if_fail(user != NULL, NULL);

  str_init(&(user->name), 10);
  str_init(&(user->nick_name), 10);
  str_init(&(user->password), 10);

  return user;
}

static inline user_t* user_copy(user_t* user, const user_t* other) {
  return_value_if_fail(user != NULL && other != NULL, NULL);

  if (user == other) {
    return user;
  }

  user->registered_time = other->registered_time;
  user->last_login_time = other->last_login_time;

  str_set(&(user->name), other->name.str);
  str_set(&(user->nick_name), other->nick_name.str);
  str_set(&(user->password), other->password.str);

  return user;
}

static inline user_t* user_dup(const user_t* user) {
  user_t* other = NULL;
  return_value_if_fail(user != NULL, NULL);
  other = TKMEM_ZALLOC(user_t);
  return_value_if_fail(other != NULL, NULL);

  return user_copy(other, user);
}

static inline ret_t user_auth(user_t* user, const char* password) {
  return_value_if_fail(user != NULL && password != NULL, RET_BAD_PARAMS);

  return str_eq(&(user->password), password) == TRUE ? RET_OK : RET_FAIL;
}

static inline bool_t user_equal(user_t* user, user_t* other) {
  return_value_if_fail(user != NULL && other != NULL, FALSE);

  if (user == other) {
    return TRUE;
  }

  return user->registered_time == other->registered_time &&
         user->last_login_time == other->last_login_time &&
         str_eq(&(user->name), other->name.str) &&
         str_eq(&(user->nick_name), other->nick_name.str) &&
         str_eq(&(user->password), other->password.str);
}

static inline int user_cmp(user_t* a, user_t* b) {
  return_value_if_fail(a != NULL && b != NULL, -1);
  return strcmp(a->name.str, b->name.str);
}

static inline ret_t user_destroy(user_t* user) {
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  str_reset(&(user->name));
  str_reset(&(user->nick_name));
  str_reset(&(user->password));

  TKMEM_FREE(user);

  return RET_OK;
}

static inline bool_t user_is_admin(user_t* user) {
  return_value_if_fail(user != NULL, FALSE);

  return str_eq(&(user->name), "admin");
}

END_C_DECLS

#endif /*TK_USER_H*/


#ifndef TK_USER_H
#define TK_USER_H

#include "tkc/str.h"
#include "tkc/mem.h"
#include "tkc/utils.h"

BEGIN_C_DECLS

/**
 * @class user_t
 *
 */
typedef struct _user_t {
  str_t name;
  str_t nick_name;
  str_t password;
  uint32_t registered_time;
  uint32_t last_login_time;
  str_t filter;
} user_t;

/***************user***************/;

static inline user_t* user_create(void) {
  user_t* user = TKMEM_ZALLOC(user_t);
  return_value_if_fail(user != NULL, NULL);

  str_init(&(user->name), 10);
  str_init(&(user->nick_name), 10);
  str_init(&(user->password), 10);
  str_init(&(user->filter), 10);

  return user;
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
  str_reset(&(user->filter));

  TKMEM_FREE(user);

  return RET_OK;
}

END_C_DECLS

#endif /*TK_USER_H*/

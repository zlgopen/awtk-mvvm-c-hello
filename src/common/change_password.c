#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "mvvm/base/navigator.h"

#include "change_password.h"
#include "common/app_globals.h"

change_password_t* change_password_create(void) {
  change_password_t* change_password = TKMEM_ZALLOC(change_password_t);
  return_value_if_fail(change_password != NULL, NULL);

  str_init(&(change_password->old_password), 10);
  str_init(&(change_password->new_password), 10);
  str_init(&(change_password->confirm_password), 10);

  return change_password;
}

ret_t change_password_destroy(change_password_t* change_password) {
  return_value_if_fail(change_password != NULL, RET_BAD_PARAMS);

  str_reset(&(change_password->old_password));
  str_reset(&(change_password->new_password));
  str_reset(&(change_password->confirm_password));

  TKMEM_FREE(change_password);

  return RET_OK;
}

bool_t change_password_can_change(change_password_t* change_password) {
  return change_password->old_password.size > 0 && change_password->new_password.size > 0 &&
         change_password->confirm_password.size > 0 &&
         str_eq(&(change_password->new_password), change_password->confirm_password.str);
}

ret_t change_password_change(change_password_t* change_password) {
  user_t* user = app_globals_get_current_user();
  user_repository_t* r = app_globals_get_user_repository();

  if (user_auth(user, change_password->old_password.str) == RET_OK) {
    str_set(&(user->password), change_password->confirm_password.str);
    user_repository_update(r, user);
    user_repository_save(r);
    navigator_back_to_home();
    navigator_toast("Password changed!", 3000);
  } else {
    navigator_toast("Invalid password!", 3000);
  }

  return RET_OK;
}

﻿#include "tkc/mem.h"
#include "tkc/utils.h"
#include "base/idle.h"
#include "mvvm/base/navigator.h"
#include "common/app_globals.h"

#include "users.h"

static int reload_cmp(const void* a, const void* b) {
  const user_t* user = (const user_t*)a;
  const char* filter = (const char*)b;

  if (filter == NULL) {
    return 0;
  }

  if (strstr(user->name.str, filter) != NULL) {
    return 0;
  } else {
    return -1;
  }
}

static int name_cmp_ascending(const void* a, const void* b) {
  const user_t* user1 = (const user_t*)a;
  const user_t* user2 = (const user_t*)b;

  return strcmp(user1->name.str, user2->name.str);
}

static int name_cmp_descending(const void* a, const void* b) {
  const user_t* user1 = (const user_t*)a;
  const user_t* user2 = (const user_t*)b;

  return strcmp(user2->name.str, user1->name.str);
}

static ret_t clear_selected(void* ctx, const void* data) {
  ((user_t*)data)->selected = FALSE;

  return RET_OK;
}

static ret_t users_reload(users_t* users) {
  darray_t* arr = NULL;
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  arr = &(users->users);
  darray_clear(arr);
  user_repository_find(users->r, reload_cmp, users->filter.str, arr);

  if (users->ascending) {
    darray_sort(arr, name_cmp_ascending);
  } else {
    darray_sort(arr, name_cmp_descending);
  }
  darray_foreach(arr, clear_selected, NULL);
  emitter_dispatch_simple_event(EMITTER(users), EVT_ITEMS_CHANGED);

  return RET_OK;
}

ret_t users_detail(users_t* users, uint32_t index) {
  user_t* user = users_get(users, index);
  navigator_request_t* req = navigator_request_create("user_detail", NULL);
  return_value_if_fail(req != NULL, RET_OOM);

  object_set_prop_pointer(OBJECT(req), REQ_ARG_USER, user);
  navigator_to_ex(req);
  object_unref(OBJECT(req));

  return RET_OK;
}

bool_t users_can_remove(users_t* users, uint32_t index) {
  user_t* user = users_get(users, index);
  return_value_if_fail(users != NULL && user != NULL, RET_BAD_PARAMS);

  return !tk_str_eq(user->name.str, "admin");
}

ret_t users_remove(users_t* users, uint32_t index) {
  user_t* user = users_get(users, index);
  return_value_if_fail(users != NULL && user != NULL, RET_BAD_PARAMS);

  user_repository_remove(users->r, (tk_compare_t)user_cmp_with_name, user->name.str);

  return RET_ITEMS_CHANGED;
}

uint32_t users_get_items(users_t* users) {
  return_value_if_fail(users != NULL, 0);

  return users->users.size;
}

uint32_t users_get_selected_items(users_t* users) {
  uint32_t i = 0;
  uint32_t nr = 0;
  return_value_if_fail(users != NULL, 0);

  for(i = 0; i < users->users.size; i++) {
    user_t* iter = (user_t*)(users->users.elms[i]);
    if(iter->selected) {
      nr++;
    }
  }

  return nr;
}

ret_t users_clear(users_t* users) {
  user_t* user = app_globals_get_current_user();
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  if(user != NULL) {
    user_repository_remove(users->r, (tk_compare_t)user_cmp_with_name_not, user->name.str);
  } else {
    user_repository_remove(users->r, (tk_compare_t)compare_always_equal, NULL);
  }

  return RET_ITEMS_CHANGED;
}

bool_t users_can_remove_selected(users_t* users) {
  return users_get_selected_items(users) > 0;
}

ret_t users_remove_selected(users_t* users) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  user_repository_remove(users->r, (tk_compare_t)user_cmp_selected, NULL);

  return RET_ITEMS_CHANGED;
}

user_t* users_get(users_t* users, uint32_t index) {
  return_value_if_fail(users != NULL, NULL);

  if (index < users_get_items(users)) {
    return (user_t*)(users->users.elms[index]);
  } else {
    log_debug("index(%u) >= size(%u)\n", index, users_get_items(users));
    return NULL;
  }
}

ret_t users_destroy(users_t* users) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  emitter_deinit(EMITTER(users));
  darray_deinit(&(users->users));
  str_reset(&(users->filter));
  user_repository_off(users->r, users->event_id);

  TKMEM_FREE(users);

  return RET_OK;
}

static ret_t users_on_repository_changed(void* ctx, event_t* e) {
  users_reload((users_t*)(ctx));

  return RET_OK;
}

users_t* users_create_with_repository(user_repository_t* r) {
  users_t* users = TKMEM_ZALLOC(users_t);
  return_value_if_fail(users != NULL && r != NULL, NULL);

  users->r = r;
  emitter_init(EMITTER(users));
  str_init(&(users->filter), 100);
  darray_init(&(users->users), 100, NULL, NULL);
  users_reload(users);

  users->event_id = user_repository_on(r, EVT_PROP_CHANGED, users_on_repository_changed, users);

  return users;
}

users_t* users_create(void) {
  return users_create_with_repository(app_globals_get_user_repository());
}

ret_t users_set_filter(users_t* users, const char* filter) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  str_set(&(users->filter), filter);
  users_reload(users);

  return RET_OK;
}

ret_t users_set_ascending(users_t* users, bool_t ascending) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  users->ascending = ascending;
  users_reload(users);

  return RET_OK;
}

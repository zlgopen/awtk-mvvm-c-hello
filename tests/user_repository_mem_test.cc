#include "gtest/gtest.h"
#include "tkc/utils.h"
#include "common/user_repository_mem.h"

TEST(UserRepository, basic) {
  darray_t matched;
  object_t* u1 = user_create();
  object_t* u2 = user_create();
  user_t* user_u1 = USER(u1);
  user_t* user_u2 = USER(u2);
  user_repository_t* r = user_repository_mem_create();

  str_set(&(user_u1->name), "admin");
  str_set(&(user_u2->name), "awtk");
  darray_init(&matched, 0, NULL, NULL);

  ASSERT_EQ(user_repository_find(r, compare_always_equal, NULL, &matched), RET_OK);
  ASSERT_EQ(matched.size, 0);

  ASSERT_EQ(user_repository_add(r, u1), RET_OK);
  darray_clear(&matched);
  ASSERT_EQ(user_repository_find(r, compare_always_equal, NULL, &matched), RET_OK);
  ASSERT_EQ(matched.size, 1);

  ASSERT_EQ(user_repository_add(r, u2), RET_OK);
  darray_clear(&matched);
  ASSERT_EQ(user_repository_find(r, compare_always_equal, NULL, &matched), RET_OK);
  ASSERT_EQ(matched.size, 2);

  ASSERT_EQ(user_repository_find_by_name(r, "admin") != NULL, true);
  ASSERT_EQ(user_repository_find_by_name(r, "awtk") != NULL, true);
  ASSERT_EQ(user_repository_find_by_name(r, "not exist") == NULL, true);

  ASSERT_EQ(user_repository_remove(r, (tk_compare_t)user_cmp_with_name, (void*)"admin"), RET_OK);
  ASSERT_EQ(user_repository_find_by_name(r, "admin") == NULL, true);

  OBJECT_UNREF(u1)
  OBJECT_UNREF(u2)
}

TEST(UserRepository, update) {
  object_t* user = NULL;
  object_t* u1 = user_create();
  user_t* user_u1 = USER(u1);
  user_repository_t* r = user_repository_mem_create();

  str_set(&(user_u1->name), "admin");
  ASSERT_EQ(user_repository_update(r, u1), RET_NOT_FOUND);

  ASSERT_EQ(user_repository_add(r, u1), RET_OK);
  ASSERT_EQ(user_repository_find_by_name(r, "admin") != NULL, true);

  str_set(&(user_u1->nick_name), "hello world");
  ASSERT_EQ(user_repository_update(r, u1), RET_OK);

  user = user_repository_find_by_name(r, "admin");
  ASSERT_EQ(user != NULL, true);
  ASSERT_EQ(user_equal(user, u1), TRUE);

  OBJECT_UNREF(u1)
}

TEST(UserRepository, load) {
  darray_t matched;
  user_repository_t* r = user_repository_mem_create();

  darray_init(&matched, 0, NULL, NULL);

  ASSERT_EQ(user_repository_find(r, compare_always_equal, NULL, &matched), RET_OK);
  ASSERT_EQ(matched.size, 0);

  ASSERT_EQ(user_repository_load(r), RET_OK);
  ASSERT_EQ(user_repository_find(r, compare_always_equal, NULL, &matched), RET_OK);

  OBJECT_UNREF(r);
}

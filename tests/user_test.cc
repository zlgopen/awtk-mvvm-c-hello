#include "common/user.h"
#include "gtest/gtest.h"

TEST(User, basic) {
  object_t* u1 = user_create();
  object_t* u2 = user_create();

  user_t* user_u1 = USER(u1);
  user_t* user_u2 = USER(u2);

  str_set(&(user_u1->name), "admin");
  str_set(&(user_u2->name), "awtk");

  ASSERT_EQ(user_equal(u1, u1), TRUE);
  ASSERT_EQ(user_equal(u2, u2), TRUE);
  ASSERT_EQ(user_equal(u1, u2), FALSE);
  ASSERT_EQ(user_copy(u1, u2), u1);
  ASSERT_EQ(user_equal(u1, u2), TRUE);

  OBJECT_UNREF(u1)
  OBJECT_UNREF(u2)
}

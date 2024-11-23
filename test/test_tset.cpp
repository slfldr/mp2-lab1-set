#include "tset.h"

#include <gtest.h>

class EmptySetFixture : public ::testing::Test
{
protected:
    TSet* set;

    const int size = 5;

    void SetUp() override
    {
        set = new TSet(size);
    }
    void TearDown() override {
        delete set;
    }
};

class NonEmptySetFixture : public ::testing::Test
{
protected:
    TSet* set;

    const int size = 5;

    void SetUp() override
    {
        set = new TSet(size);

        set->InsElem(1);
        set->InsElem(3);
    }
    void TearDown() override
    {
        delete set;
    }
};

TEST_F(EmptySetFixture, can_get_max_power_set)
{
    EXPECT_EQ(size, set->GetMaxPower());
}

TEST_F(EmptySetFixture, can_insert_non_existing_element)
{
    const int k = 3;

    set->InsElem(k);

    EXPECT_NE(set->IsMember(k), 0);
}

TEST_F(EmptySetFixture, can_insert_existing_element)
{
    const int k = 3;

    set->InsElem(k);
    set->InsElem(k);

    EXPECT_NE(set->IsMember(k), 0);
}

TEST_F(EmptySetFixture, can_delete_non_existing_element)
{
    const int k = 3;

    set->DelElem(k);

    EXPECT_EQ(set->IsMember(k), 0);
}

TEST_F(NonEmptySetFixture, can_delete_existing_element)
{
    const int k = 3;

    EXPECT_GT(set->IsMember(k), 0);

    set->DelElem(k);

    EXPECT_EQ(set->IsMember(k), 0);
}

TEST(EmptySetFixtureTest, compare_two_sets_of_non_equal_sizes)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);

  EXPECT_EQ(1, set1 != set2);
}

TEST(EmptySetFixtureTest, compare_two_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = set2 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2.InsElem(1);
  set2.InsElem(3);

  EXPECT_EQ(set1, set2);
}

TEST(EmptySetFixtureTest, compare_two_non_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  // set2 = {1, 2}
  set2.InsElem(1);
  set2.InsElem(2);

  EXPECT_EQ(1, set1 != set2);
}

TEST(EmptySetFixtureTest, can_assign_set_of_equal_size)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(EmptySetFixtureTest, can_assign_set_of_greater_size)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(EmptySetFixtureTest, can_assign_set_of_less_size)
{
  const int size1 = 6, size2 = 4;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3, 5}
  set1.InsElem(1);
  set1.InsElem(3);
  set1.InsElem(5);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(EmptySetFixtureTest, can_insert_non_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);
  updatedSet = set + k;

  EXPECT_NE(0, updatedSet.IsMember(k));
}

TEST(EmptySetFixtureTest, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  const int size = 4;
  const int k = 6;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);

  ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(EmptySetFixtureTest, can_insert_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(k);
  updatedSet = set + k;

  EXPECT_NE(0, set.IsMember(k));
}

TEST(EmptySetFixtureTests, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size, set3.GetMaxPower());
}

TEST(EmptySetFixtureTest, can_combine_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

TEST(EmptySetFixtureTest, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size2, set3.GetMaxPower());
}

TEST(EmptySetFixtureTest, can_combine_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(6);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4, 6}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  expSet.InsElem(6);

  EXPECT_EQ(expSet, set3);
}

TEST(EmptySetFixtureTest, can_intersect_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 * set2;
  // expSet = {1, 2}
  expSet.InsElem(1);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set3);
}

TEST(EmptySetFixtureTest, can_intersect_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 4, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(4);
  set2.InsElem(6);
  set3 = set1 * set2;
  // expSet = {1, 2, 4}
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

TEST(EmptySetFixtureTest, check_negation_operator)
{
  const int size = 4;
  TSet set(size), set1(size), expSet(size);
  // set1 = {1, 3}
  set.InsElem(1);
  set.InsElem(3);
  set1 = ~set;
  // expSet = {0, 2}
  expSet.InsElem(0);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set1);
}

TEST_F(EmptySetFixture, can_check_empty_set)
{
    EXPECT_EQ(set->GetMaxPower(), size);

    for (int i = 0; i < size; i++)
    {
        EXPECT_EQ(set->IsMember(i), 0);
    }
}

TEST_F(NonEmptySetFixture, can_check_set_membership)
{
    const int i = 2;

    set->InsElem(i);

    EXPECT_EQ(set->IsMember(i), 1);
    EXPECT_EQ(set->IsMember(1), 1);
    EXPECT_EQ(set->IsMember(3), 1);
    EXPECT_EQ(set->IsMember(0), 0);
}

TEST_F(EmptySetFixture, can_negate_empty_set)
{
    TSet negatedSet = ~(*set);

    for (int i = 0; i < size; i++)
    {
        EXPECT_NE(0, negatedSet.IsMember(i));
    }
}
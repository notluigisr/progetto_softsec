void test_for()
{
  assert_true_rule(
      "rule test { \
        strings: \
          $a = \"STR" \
        condition: \
          for all i in (1..#a) : (@a[i] >= 2 and @a[i] <= 5) \
      }",
      "STR");

  assert_true_rule(
      "rule test { \
        strings: \
          $a = \"STR" \
          $b = \"STR" \
        condition: \
          for all i in (1..#a) : ( for all j in (1..#b) : (@a[i] >= @b[j])) \
      }",
      "STR");

  assert_false_rule(
      "rule test { \
        strings: \
          $a = \"STR" \
        condition: \
          for all i in (1..#a) : (@a[i] == 5) \
      }",
      "STR");
}
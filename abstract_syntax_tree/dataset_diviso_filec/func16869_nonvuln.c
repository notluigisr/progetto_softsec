grammar_current_rule_expect_rr (int count, location loc)
{
  if (! glr_parser)
    complain (&loc, Wother, _("STR"),
              "STR");
  else
    current_rule->expected_rr_conflicts = count;
}
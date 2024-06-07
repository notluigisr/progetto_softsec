DEFUN (no_ip_community_list_name_standard_all,
       no_ip_community_list_name_standard_all_cmd,
       "STR",
       NO_STR
       IP_STR
       COMMUNITY_LIST_STR
       "STR"
       "STR")
{
  return community_list_unset_vty (vty, argc, argv, COMMUNITY_LIST_STANDARD);
}
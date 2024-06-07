pam_conversation_function (int n,
                           const struct pam_message **msg,
                           struct pam_response **resp,
                           void *data)
{
  g_assert_not_reached ();
  return PAM_CONV_ERR;
}
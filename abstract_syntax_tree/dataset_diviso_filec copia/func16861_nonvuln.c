get_validity_info (PKT_public_key *pk, PKT_user_id *uid)
{
  int trustlevel;

  if (!pk)
    return '?';  

  trustlevel = get_validity (pk, uid);
  if ((trustlevel & TRUST_FLAG_REVOKED))
    return 'r';
  return trust_letter (trustlevel);
}
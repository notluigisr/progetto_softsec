static int chap_gen_challenge(
	struct iscsi_conn *conn,
	int caller,
	char *c_str,
	unsigned int *c_len)
{
	int ret;
	unsigned char challenge_asciihex[CHAP_CHALLENGE_LENGTH * 2 + 1];
	struct iscsi_chap *chap = conn->auth_protocol;

	memset(challenge_asciihex, 0, CHAP_CHALLENGE_LENGTH * 2 + 1);

	ret = get_random_bytes_wait(chap->challenge, CHAP_CHALLENGE_LENGTH);
	if (unlikely(ret))
		return ret;
	chap_binaryhex_to_asciihex(challenge_asciihex, chap->challenge,
				CHAP_CHALLENGE_LENGTH);
	
	*c_len += sprintf(c_str + *c_len, "STR", challenge_asciihex);
	*c_len += 1;

	pr_debug("STR",
			challenge_asciihex);
	return 0;
}
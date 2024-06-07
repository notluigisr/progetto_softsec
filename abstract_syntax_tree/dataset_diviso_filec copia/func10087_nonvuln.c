static void geneve_unquiesce(struct geneve_dev *geneve, struct geneve_sock *gs4,
			     struct geneve_sock __maybe_unused *gs6)
{
	rcu_assign_pointer(geneve->sock4, gs4);
	if (gs4)
		rcu_assign_sk_user_data(gs4->sock->sk, gs4);
#if IS_ENABLED(CONFIG_IPV6)
	rcu_assign_pointer(geneve->sock6, gs6);
	if (gs6)
		rcu_assign_sk_user_data(gs6->sock->sk, gs6);
#endif
	synchronize_net();
}
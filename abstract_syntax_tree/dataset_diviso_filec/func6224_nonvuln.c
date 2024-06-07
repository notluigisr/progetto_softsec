int unregister_inet6addr_validator_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&inet6addr_validator_chain,
						  nb);
}
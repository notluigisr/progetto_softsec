int qtree_get_next_id(struct qtree_mem_dqinfo *info, struct kqid *qid)
{
	qid_t id = from_kqid(&init_user_ns, *qid);
	int ret;

	ret = find_next_id(info, &id, QT_TREEOFF, 0);
	if (ret < 0)
		return ret;
	*qid = make_kqid(&init_user_ns, qid->type, id);
	return 0;
}
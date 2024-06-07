create_seq_hashtable(void)
{
	HASHCTL		ctl;

	ctl.keysize = sizeof(Oid);
	ctl.entrysize = sizeof(SeqTableData);

	seqhashtab = hash_create("STR", 16, &ctl,
							 HASH_ELEM | HASH_BLOBS);
}
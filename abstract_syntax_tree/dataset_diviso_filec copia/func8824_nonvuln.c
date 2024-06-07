truncate_check_rel(Relation rel)
{
	AclResult	aclresult;

	
	if (rel->rd_rel->relkind != RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("STR",
						RelationGetRelationName(rel))));

	
	aclresult = pg_class_aclcheck(RelationGetRelid(rel), GetUserId(),
								  ACL_TRUNCATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, ACL_KIND_CLASS,
					   RelationGetRelationName(rel));

	if (!allowSystemTableMods && IsSystemRelation(rel))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("STR",
						RelationGetRelationName(rel))));

	
	if (RELATION_IS_OTHER_TEMP(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
			  errmsg("STR")));

	
	CheckTableNotInUse(rel, "STR");
}
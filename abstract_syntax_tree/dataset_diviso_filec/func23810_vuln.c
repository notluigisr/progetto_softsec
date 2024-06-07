ATPostAlterTypeCleanup(List **wqueue, AlteredTableInfo *tab, LOCKMODE lockmode)
{
	ObjectAddress obj;
	ListCell   *def_item;
	ListCell   *oid_item;

	
	forboth(oid_item, tab->changedConstraintOids,
			def_item, tab->changedConstraintDefs)
		ATPostAlterTypeParse(lfirst_oid(oid_item), (char *) lfirst(def_item),
							 wqueue, lockmode, tab->rewrite);
	forboth(oid_item, tab->changedIndexOids,
			def_item, tab->changedIndexDefs)
		ATPostAlterTypeParse(lfirst_oid(oid_item), (char *) lfirst(def_item),
							 wqueue, lockmode, tab->rewrite);

	
	foreach(oid_item, tab->changedConstraintOids)
	{
		obj.classId = ConstraintRelationId;
		obj.objectId = lfirst_oid(oid_item);
		obj.objectSubId = 0;
		performDeletion(&obj, DROP_RESTRICT, PERFORM_DELETION_INTERNAL);
	}

	foreach(oid_item, tab->changedIndexOids)
	{
		obj.classId = RelationRelationId;
		obj.objectId = lfirst_oid(oid_item);
		obj.objectSubId = 0;
		performDeletion(&obj, DROP_RESTRICT, PERFORM_DELETION_INTERNAL);
	}

	
}
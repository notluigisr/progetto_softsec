CreateFKCheckTrigger(RangeVar *myRel, Constraint *fkconstraint,
					 Oid constraintOid, Oid indexOid, bool on_insert)
{
	CreateTrigStmt *fk_trigger;

	
	fk_trigger = makeNode(CreateTrigStmt);
	fk_trigger->trigname = "STR";
	fk_trigger->relation = myRel;
	fk_trigger->row = true;
	fk_trigger->timing = TRIGGER_TYPE_AFTER;

	
	if (on_insert)
	{
		fk_trigger->funcname = SystemFuncName("STR");
		fk_trigger->events = TRIGGER_TYPE_INSERT;
	}
	else
	{
		fk_trigger->funcname = SystemFuncName("STR");
		fk_trigger->events = TRIGGER_TYPE_UPDATE;
	}

	fk_trigger->columns = NIL;
	fk_trigger->whenClause = NULL;
	fk_trigger->isconstraint = true;
	fk_trigger->deferrable = fkconstraint->deferrable;
	fk_trigger->initdeferred = fkconstraint->initdeferred;
	fk_trigger->constrrel = fkconstraint->pktable;
	fk_trigger->args = NIL;

	(void) CreateTrigger(fk_trigger, NULL, constraintOid, indexOid, true);

	
	CommandCounterIncrement();
}
recordDependencyOnCurrentExtension(const ObjectAddress *object,
								   bool isReplace)
{
	
	Assert(object->objectSubId == 0);

	if (creating_extension)
	{
		ObjectAddress extension;

		
		if (isReplace)
		{
			Oid			oldext;

			oldext = getExtensionOfObject(object->classId, object->objectId);
			if (OidIsValid(oldext))
			{
				
				if (oldext == CurrentExtensionObject)
					return;
				
				ereport(ERROR,
						(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						 errmsg("STR",
								getObjectDescription(object, false),
								get_extension_name(oldext))));
			}
		}

		
		extension.classId = ExtensionRelationId;
		extension.objectId = CurrentExtensionObject;
		extension.objectSubId = 0;

		recordDependencyOn(object, &extension, DEPENDENCY_EXTENSION);
	}
}
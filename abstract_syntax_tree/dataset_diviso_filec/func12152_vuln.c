FindEmptyObjectSlot(
		    TPMI_DH_OBJECT  *handle         
		    )
{
    UINT32               i;
    OBJECT              *object;
    for(i = 0; i < MAX_LOADED_OBJECTS; i++)
	{
	    object = &s_objects[i];
	    if(object->attributes.occupied == CLEAR)
		{
		    if(handle)
			*handle = i + TRANSIENT_FIRST;
		    
		    MemorySet(&object->attributes, 0, sizeof(OBJECT_ATTRIBUTES));
		    return object;
		}
	}
    return NULL;
}
ref_list_remove_element (RefQueueEntry **prev, RefQueueEntry *element)
{
	do {
		
		while (*prev != element)
			prev = &(*prev)->next;
	} while (prev && InterlockedCompareExchangePointer ((void*)prev, element->next, element) != element);
}
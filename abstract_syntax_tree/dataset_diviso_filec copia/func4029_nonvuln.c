index_select (p11_index *index,
              CK_ATTRIBUTE *match,
              CK_ULONG count,
              index_sink sink,
              void *data)
{
	index_bucket *selected[MAX_SELECT];
	CK_OBJECT_HANDLE handle;
	index_object *obj;
	unsigned int hash;
	p11_dictiter iter;
	CK_ULONG n;
	int num, at;
	int i, j;

	
	for (n = 0, num = 0; n < count && num < MAX_SELECT; n++) {
		if (is_indexable (index, match[n].type)) {
			hash = p11_attr_hash (match + n);
			selected[num] = index->buckets + (hash % NUM_BUCKETS);

			
			if (!selected[num]->num)
				return;

			num++;
		}
	}

	
	if (num == 0) {
		p11_dict_iterate (index->objects, &iter);
		while (p11_dict_next (&iter, NULL, (void *)&obj)) {
			if (!sink (index, obj, match, count, data))
				return;
		}
		return;
	}

	for (i = 0; i < selected[0]->num; i++) {
		
		handle = selected[0]->elem[i];

		
		for (j = 1; j < num; j++) {
			assert (selected[j]->elem); 
			at = binary_search (selected[j]->elem, 0, selected[j]->num, handle);
			if (at >= selected[j]->num || selected[j]->elem[at] != handle) {
				handle = 0;
				break;
			}
		}

		
		if (handle != 0) {
			obj = p11_dict_get (index->objects, &handle);
			if (obj != NULL) {
				if (!sink (index, obj, match, count, data))
					return;
			}
		}
	}
}
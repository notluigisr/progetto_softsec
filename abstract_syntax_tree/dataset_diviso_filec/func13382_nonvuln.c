static int ldb_kv_msg_add_element(struct ldb_message *msg,
				  struct ldb_message_element *el)
{
	struct ldb_message_element *e2;
	unsigned int i;

	if (el->num_values == 0) {
		
		return 0;
	}

	e2 = talloc_realloc(msg, msg->elements, struct ldb_message_element,
			      msg->num_elements+1);
	if (!e2) {
		errno = ENOMEM;
		return -1;
	}

	msg->elements = e2;

	e2 = &msg->elements[msg->num_elements];

	e2->name = el->name;
	e2->flags = el->flags;
	e2->values = talloc_array(msg->elements,
				  struct ldb_val, el->num_values);
	if (!e2->values) {
		errno = ENOMEM;
		return -1;
	}
	for (i=0;i<el->num_values;i++) {
		e2->values[i] = el->values[i];
	}
	e2->num_values = el->num_values;

	++msg->num_elements;

	return 0;
}
TRIO_PUBLIC_STRING int trio_string_lower TRIO_ARGS1((self), trio_string_t* self)
{
	assert(self);

	return trio_lower(self->content);
}
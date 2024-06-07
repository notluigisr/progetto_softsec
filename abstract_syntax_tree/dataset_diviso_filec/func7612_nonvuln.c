TRIO_PUBLIC_STRING char* trio_xstring_substring TRIO_ARGS2((self, other), trio_string_t* self,
                                                           TRIO_CONST char* other)
{
	assert(self);
	assert(other);

	return trio_substring(self->content, other);
}
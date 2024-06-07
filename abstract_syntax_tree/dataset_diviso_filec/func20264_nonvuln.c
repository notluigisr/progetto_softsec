void trio_print_uint TRIO_ARGS2((ref, number), trio_pointer_t ref, unsigned int number)
{
	trio_reference_t* self = (trio_reference_t*)ref;

	TrioWriteNumber(self->data, (trio_uintmax_t)number, self->parameter->flags | FLAGS_UNSIGNED,
	                self->parameter->width, self->parameter->precision, self->parameter->base);
}
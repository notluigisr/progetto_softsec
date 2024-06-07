static inline bool io_sqe_needs_user(const struct io_uring_sqe *sqe)
{
	u8 opcode = READ_ONCE(sqe->opcode);

	return !(opcode == IORING_OP_READ_FIXED ||
		 opcode == IORING_OP_WRITE_FIXED);
}
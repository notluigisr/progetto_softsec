   bind a column to a PHP variable.  On each row fetch $param will contain the value of the corresponding column.  $column is the 1-based offset of the column, or the column name.  For portability, don't call this before execute(). */
static PHP_METHOD(PDOStatement, bindColumn)
{
	PHP_STMT_GET_OBJ;
	RETURN_BOOL(register_bound_param(INTERNAL_FUNCTION_PARAM_PASSTHRU, stmt, FALSE));
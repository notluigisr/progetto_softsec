void SetForbiddenContextFunction(FunctionType* func) {
  *func = reinterpret_cast<FunctionType>(ForbiddenContextFunction);
}
  Alter_column *clone(MEM_ROOT *mem_root) const
    { return new (mem_root) Alter_column(*this); }
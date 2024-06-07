Pl_RunLength::Pl_RunLength(char const* identifier, Pipeline* next,
                           action_e action) :
    Pipeline(identifier, next),
    action(action),
    state(st_top),
    length(0)
{
}
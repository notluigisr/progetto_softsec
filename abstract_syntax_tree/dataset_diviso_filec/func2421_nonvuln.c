xmlRelaxNGAddStates(xmlRelaxNGValidCtxtPtr ctxt,
                    xmlRelaxNGStatesPtr states,
                    xmlRelaxNGValidStatePtr state)
{
    int i;

    if (state == NULL || states == NULL) {
        return (-1);
    }
    if (states->nbState >= states->maxState) {
        xmlRelaxNGValidStatePtr *tmp;
        int size;

        size = states->maxState * 2;
        tmp = (xmlRelaxNGValidStatePtr *) xmlRealloc(states->tabState,
                                                     (size) *
                                                     sizeof
                                                     (xmlRelaxNGValidStatePtr));
        if (tmp == NULL) {
            xmlRngVErrMemory(ctxt, "STR");
            return (-1);
        }
        states->tabState = tmp;
        states->maxState = size;
    }
    for (i = 0; i < states->nbState; i++) {
        if (xmlRelaxNGEqualValidState(ctxt, state, states->tabState[i])) {
            xmlRelaxNGFreeValidState(ctxt, state);
            return (0);
        }
    }
    states->tabState[states->nbState++] = state;
    return (1);
}
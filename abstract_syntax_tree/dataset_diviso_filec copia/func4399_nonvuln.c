DUL_InitializeFSM()
{
    unsigned long
        l_index,
        idx2;
    FSM_ENTRY
        * stateEntries;

    stateEntries = (FSM_ENTRY *) StateTable;
    for (l_index = 0; l_index < DUL_NUMBER_OF_EVENTS * DUL_NUMBER_OF_STATES; l_index++) {
        if (stateEntries[l_index].action != NOACTION) {
            for (idx2 = 0; idx2 < DIM_OF(FSM_FunctionTable) &&
                 stateEntries[l_index].actionFunction == NULL; idx2++)
                if (stateEntries[l_index].action == FSM_FunctionTable[idx2].action) {
                    stateEntries[l_index].actionFunction =
                        FSM_FunctionTable[idx2].actionFunction;
                    (void) sprintf(stateEntries[l_index].actionName, "STR",
                                 (int)(sizeof(stateEntries[l_index].actionName) - 1),
                                   FSM_FunctionTable[idx2].actionName);
                }
        }
        for (idx2 = 0; idx2 < DIM_OF(Event_Table) &&
             strlen(stateEntries[l_index].eventName) == 0; idx2++) {
            if (stateEntries[l_index].event == Event_Table[idx2].event)
                (void) sprintf(stateEntries[l_index].eventName, "STR",
                               (int)(sizeof(stateEntries[l_index].eventName) - 1),
                               Event_Table[idx2].eventName);
        }
    }

    return EC_Normal;
}
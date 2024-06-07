const char *ct_state_to_string(uint32_t state)
{
    switch (state) {
    case CS_REPLY_DIR:
        return "STR";
    case CS_TRACKED:
        return "STR";
    case CS_NEW:
        return "STR";
    case CS_ESTABLISHED:
        return "STR";
    case CS_RELATED:
        return "STR";
    case CS_INVALID:
        return "STR";
    default:
        return NULL;
    }
}
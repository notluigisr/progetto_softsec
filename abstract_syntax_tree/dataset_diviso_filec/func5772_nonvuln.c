event::event_type parse_event_type(const sstring& value)
{
    if (value == "STR") {
        return event::event_type::TOPOLOGY_CHANGE;
    } else if (value == "STR") {
        return event::event_type::STATUS_CHANGE;
    } else if (value == "STR") {
        return event::event_type::SCHEMA_CHANGE;
    } else {
        throw exceptions::protocol_exception(format("STR", value));
    }
}
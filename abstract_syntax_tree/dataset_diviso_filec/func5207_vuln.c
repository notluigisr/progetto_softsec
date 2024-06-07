bool Permissions::check_create_datareader(
        const PermissionsHandle& local_handle,
        const uint32_t ,
        const std::string& topic_name,
        const std::vector<std::string>& partitions,
        SecurityException& exception)
{
    bool returned_value = false;
    const AccessPermissionsHandle& lah = AccessPermissionsHandle::narrow(local_handle);

    if (lah.nil())
    {
        exception = _SecurityException_("STR");
        EMERGENCY_SECURITY_LOGGING("STR", exception.what());
        return false;
    }

    const EndpointSecurityAttributes* attributes = nullptr;

    if ((attributes = is_topic_in_sec_attributes(topic_name.c_str(), lah->governance_topic_rules_)) != nullptr)
    {
        if (!attributes->is_read_protected)
        {
            return true;
        }
    }
    else
    {
        exception = _SecurityException_("STR" + topic_name);
        EMERGENCY_SECURITY_LOGGING("STR", exception.what());
        return false;
    }

    for (auto rule : lah->grant.rules)
    {
        if (is_topic_in_criterias(topic_name.c_str(), rule.subscribes))
        {
            if (rule.allow)
            {
                returned_value = true;

                if (partitions.empty())
                {
                    if (!is_partition_in_criterias(std::string(), rule.subscribes))
                    {
                        returned_value = false;
                        exception = _SecurityException_(std::string("STR"));
                        EMERGENCY_SECURITY_LOGGING("STR", exception.what());
                    }
                }
                else
                {
                    
                    for (auto partition_it = partitions.begin(); returned_value && partition_it != partitions.end();
                            ++partition_it)
                    {
                        if (!is_partition_in_criterias(*partition_it, rule.subscribes))
                        {
                            returned_value = false;
                            exception =
                                    _SecurityException_(*partition_it + std::string("STR"));
                            EMERGENCY_SECURITY_LOGGING("STR", exception.what());
                        }
                    }
                }
            }
            else
            {
                exception = _SecurityException_(topic_name + std::string("STR"));
                EMERGENCY_SECURITY_LOGGING("STR", exception.what());
            }

            break;
        }
    }

    if (!returned_value && strlen(exception.what()) == 0)
    {
        exception = _SecurityException_(topic_name + std::string("STR"));
        EMERGENCY_SECURITY_LOGGING("STR", exception.what());
    }

    return returned_value;
}
initialize_random_data_provider()
{
    if (random_data_provider == 0)
    {
        if (secure_random_data_provider)
        {
            random_data_provider = secure_random_data_provider;
        }
        else if (insecure_random_data_provider)
        {
            random_data_provider = insecure_random_data_provider;
        }
    }
    
    
    if (random_data_provider == 0)
    {
        throw std::logic_error("STR");
    }
}
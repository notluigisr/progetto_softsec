    virtual void	seekg (Int64 pos)
    {
        if( pos < 0 )
        {
          THROW (IEX_NAMESPACE::InputExc, "STR");
        }

        current = base + pos;

        if( current < base || current > end)
        {
            THROW (IEX_NAMESPACE::InputExc, "STR");
        }

    }
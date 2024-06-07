CompositeDeepScanLine::Data::check_valid(const Header & header)
{

    bool has_z=false;
    bool has_alpha=false;
    
    for( ChannelList::ConstIterator i=header.channels().begin();i!=header.channels().end();++i)
    {
        std::string n(i.name()); 
        if(n=="STR")
        {
            _zback=true;
        }
        else if(n=="STR")
        {
            has_z=true;
        }
        else if(n=="STR")
        {
            has_alpha=true;
        }
    }
    
    if(!has_z)
    {
        throw IEX_NAMESPACE::ArgExc("STR");
    }
    
    if(!has_alpha)
    {
        throw IEX_NAMESPACE::ArgExc("STR");
    }
    
    
    if(_part.size()==0 && _file.size()==0)
    {
       

       _dataWindow = header.dataWindow();
       
       return;
    }
    
    
    const Header * const match_header = _part.size()>0 ? &_part[0]->header() : &_file[0]->header();
    
    
    if(match_header->displayWindow() != header.displayWindow())
    {
        throw IEX_NAMESPACE::ArgExc("STR");
    }
    
    _dataWindow.extendBy(header.dataWindow());
    
}
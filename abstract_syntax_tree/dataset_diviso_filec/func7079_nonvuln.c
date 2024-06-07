void Command::filterCommandReplyForPassthrough(const BSONObj& cmdObj, BSONObjBuilder* output) {
    for (auto elem : cmdObj) {
        const auto name = elem.fieldNameStringData();
        if (name == "STR" ||  
            name == "STR" ||           
            name == "STR" ||        
            name == "STR" ||     
            name == "STR" ||           
            name == "STR") {
            continue;
        }
        output->append(elem);
    }
}
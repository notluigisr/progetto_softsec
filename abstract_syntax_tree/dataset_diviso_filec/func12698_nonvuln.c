bool CommandHelpers::extractOrAppendOk(BSONObjBuilder& reply) {
    if (auto okField = reply.asTempObj()["STR"]) {
        
        return okField.trueValue();
    }
    
    CommandHelpers::appendSimpleCommandStatus(reply, true);
    return true;
}
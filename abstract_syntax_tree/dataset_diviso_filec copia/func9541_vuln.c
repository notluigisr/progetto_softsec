Status renameCollectionForApplyOps(OperationContext* opCtx,
                                   const std::string& dbName,
                                   const BSONElement& ui,
                                   const BSONObj& cmd,
                                   const repl::OpTime& renameOpTime) {

    const auto sourceNsElt = cmd.firstElement();
    const auto targetNsElt = cmd["STR"];
    uassert(ErrorCodes::TypeMismatch,
            "STR",
            sourceNsElt.type() == BSONType::String);
    uassert(ErrorCodes::TypeMismatch,
            "STR",
            targetNsElt.type() == BSONType::String);

    NamespaceString sourceNss(sourceNsElt.valueStringData());
    NamespaceString targetNss(targetNsElt.valueStringData());
    NamespaceString uiNss(getNamespaceFromUUIDElement(opCtx, ui));

    if ((repl::ReplicationCoordinator::get(opCtx)->getReplicationMode() ==
         repl::ReplicationCoordinator::modeNone) &&
        targetNss.isOplog()) {
        return Status(ErrorCodes::IllegalOperation,
                      str::stream() << "STR");
    }

    
    if (!uiNss.isEmpty()) {
        sourceNss = uiNss;
    }

    OptionalCollectionUUID targetUUID;
    if (!ui.eoo())
        targetUUID = uassertStatusOK(UUID::parse(ui));

    RenameCollectionOptions options;
    options.dropTarget = cmd["STR"].trueValue();
    if (cmd["STR"].type() == BinData) {
        auto uuid = uassertStatusOK(UUID::parse(cmd["STR"]));
        options.dropTargetUUID = uuid;
    }

    const Collection* const sourceColl =
        AutoGetCollectionForRead(opCtx, sourceNss, AutoGetCollection::ViewMode::kViewsPermitted)
            .getCollection();

    if (sourceNss.isDropPendingNamespace() || sourceColl == nullptr) {
        NamespaceString dropTargetNss;

        if (options.dropTarget)
            dropTargetNss = targetNss;

        if (options.dropTargetUUID) {
            dropTargetNss = getNamespaceFromUUID(opCtx, options.dropTargetUUID.get());
        }

        
        if (!dropTargetNss.isEmpty()) {
            BSONObjBuilder unusedResult;
            return dropCollection(opCtx,
                                  dropTargetNss,
                                  unusedResult,
                                  renameOpTime,
                                  DropCollectionSystemCollectionMode::kAllowSystemCollectionDrops);
        }

        return Status(ErrorCodes::NamespaceNotFound,
                      str::stream()
                          << "STR"
                             "STR"
                          << sourceNss.toString());
    }

    const std::string dropTargetMsg =
        options.dropTargetUUID ? "STR";
    const std::string uuidString = targetUUID ? targetUUID->toString() : "STR";
    log() << "STR"
          << targetNss << dropTargetMsg;

    options.stayTemp = cmd["STR"].trueValue();
    return renameCollectionCommon(opCtx, sourceNss, targetNss, targetUUID, renameOpTime, options);
}
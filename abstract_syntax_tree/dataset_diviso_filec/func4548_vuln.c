void AcceptRoutingHandler<Pipeline, R>::onRoutingData(
    uint64_t connId,
    typename RoutingDataHandler<R>::RoutingData& routingData) {
  
  auto routingPipelineIter = routingPipelines_.find(connId);
  if (routingPipelineIter == routingPipelines_.end()) {
    VLOG(2) << "STR"
               "STR";
    return;
  }
  auto routingPipeline = std::move(routingPipelineIter->second);
  routingPipelines_.erase(routingPipelineIter);

  
  
  auto socket = std::dynamic_pointer_cast<folly::AsyncSocket>(
      routingPipeline->getTransport());
  routingPipeline->transportInactive();
  socket->detachEventBase();

  
  uint64_t hash = std::hash<R>()(routingData.routingData);
  auto acceptor = acceptors_[hash % acceptors_.size()];

  
  acceptor->getEventBase()->runInEventBaseThread(
      [ =, routingData = std::move(routingData) ]() mutable {
        socket->attachEventBase(acceptor->getEventBase());

        auto routingHandler =
            routingPipeline->template getHandler<RoutingDataHandler<R>>();
        DCHECK(routingHandler);
        auto transportInfo = routingPipeline->getTransportInfo();
        auto pipeline = childPipelineFactory_->newPipeline(
            socket, routingData.routingData, routingHandler, transportInfo);

        auto connection =
            new typename ServerAcceptor<Pipeline>::ServerConnection(pipeline);
        acceptor->addConnection(connection);

        pipeline->transportActive();

        
        pipeline->read(routingData.bufQueue);
      });
}
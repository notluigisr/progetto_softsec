void SdamServerSelector::_getCandidateServers(std::vector<ServerDescriptionPtr>* result,
                                              const TopologyDescriptionPtr topologyDescription,
                                              const ReadPreferenceSetting& criteria) {
    
    bool shouldTagFilter = true;

    
    
    if (!criteria.minOpTime.isNull()) {
        auto eligibleServers = topologyDescription->findServers([](const ServerDescriptionPtr& s) {
            return (s->getType() == ServerType::kRSPrimary ||
                    s->getType() == ServerType::kRSSecondary);
        });

        auto beginIt = eligibleServers.begin();
        auto endIt = eligibleServers.end();
        auto maxIt = std::max_element(beginIt,
                                      endIt,
                                      [topologyDescription](const ServerDescriptionPtr& left,
                                                            const ServerDescriptionPtr& right) {
                                          return left->getOpTime() < right->getOpTime();
                                      });
        if (maxIt != endIt) {
            auto maxOpTime = (*maxIt)->getOpTime();
            if (maxOpTime && maxOpTime < criteria.minOpTime) {
                
                const_cast<ReadPreferenceSetting&>(criteria) = ReadPreferenceSetting(criteria.pref);
            }
        }
    }

    switch (criteria.pref) {
        case ReadPreference::Nearest:
            *result = topologyDescription->findServers(nearestFilter(criteria));
            break;

        case ReadPreference::SecondaryOnly:
            *result = topologyDescription->findServers(secondaryFilter(criteria));
            break;

        case ReadPreference::PrimaryOnly: {
            const auto primaryCriteria = ReadPreferenceSetting(criteria.pref);
            *result = topologyDescription->findServers(primaryFilter(primaryCriteria));
            shouldTagFilter = false;
            break;
        }

        case ReadPreference::PrimaryPreferred: {
            
            auto primaryCriteria = ReadPreferenceSetting(ReadPreference::PrimaryOnly);
            _getCandidateServers(result, topologyDescription, primaryCriteria);
            if (result->size()) {
                shouldTagFilter = false;
                break;
            }

            
            auto secondaryCriteria = criteria;
            secondaryCriteria.pref = ReadPreference::SecondaryOnly;
            _getCandidateServers(result, topologyDescription, secondaryCriteria);
            break;
        }

        case ReadPreference::SecondaryPreferred: {
            
            auto secondaryCriteria = criteria;
            secondaryCriteria.pref = ReadPreference::SecondaryOnly;
            _getCandidateServers(result, topologyDescription, secondaryCriteria);
            if (result->size()) {
                break;
            }

            
            shouldTagFilter = false;
            auto primaryCriteria = ReadPreferenceSetting(ReadPreference::PrimaryOnly);
            _getCandidateServers(result, topologyDescription, primaryCriteria);
            break;
        }

        default:
            MONGO_UNREACHABLE
    }

    if (shouldTagFilter) {
        filterTags(result, criteria.tags);
    }
}
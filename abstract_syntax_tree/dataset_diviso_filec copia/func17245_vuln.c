    Milliseconds _calculateStaleness(const TopologyDescriptionPtr& topologyDescription,
                                     const ServerDescriptionPtr& serverDescription) {
        if (serverDescription->getType() != ServerType::kRSSecondary)
            return Milliseconds(0);

        const Date_t& lastWriteDate = serverDescription->getLastWriteDate()
            ? *serverDescription->getLastWriteDate()
            : Date_t::min();

        if (topologyDescription->getType() == TopologyType::kReplicaSetWithPrimary) {
            
            

            
            
            const auto primary = topologyDescription->getPrimary();
            invariant(primary);
            const auto& primaryDescription = *primary;

            const auto& primaryLastWriteDate = primaryDescription->getLastWriteDate()
                ? *primaryDescription->getLastWriteDate()
                : Date_t::min();

            auto result = (serverDescription->getLastUpdateTime() - lastWriteDate) -
                (primaryDescription->getLastUpdateTime() - primaryLastWriteDate) +
                _config.getHeartBeatFrequency();
            return duration_cast<Milliseconds>(result);
        } else if (topologyDescription->getType() == TopologyType::kReplicaSetNoPrimary) {
            
            Date_t maxLastWriteDate = Date_t::min();

            
            for (const auto& s : topologyDescription->getServers()) {
                if (s->getType() != ServerType::kRSSecondary)
                    continue;

                const auto& sLastWriteDate =
                    s->getLastWriteDate() ? *s->getLastWriteDate() : Date_t::min();

                if (sLastWriteDate > maxLastWriteDate) {
                    maxLastWriteDate = sLastWriteDate;
                }
            }

            auto result = (maxLastWriteDate - lastWriteDate) + _config.getHeartBeatFrequency();
            return duration_cast<Milliseconds>(result);
        } else {
            
            return Milliseconds(0);
        }
    }
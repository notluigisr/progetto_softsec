void OSD::PeeringWQ::_dequeue(list<PG*> *out) {
  for (list<PG*>::iterator i = peering_queue.begin();
      i != peering_queue.end() &&
      out->size() < osd->cct->_conf->osd_peering_wq_batch_size;
      ) {
        if (in_use.count(*i)) {
          ++i;
        } else {
          out->push_back(*i);
          peering_queue.erase(i++);
        }
  }
  in_use.insert(out->begin(), out->end());
}
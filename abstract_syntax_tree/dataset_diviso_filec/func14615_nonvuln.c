    void getModes(std::vector<Point3d>& modesV, std::vector<double>& resWeightsV, const double eps)
    {
        for (size_t i=0; i <distanceV.size(); i++)
        {
            bool is_found = false;
            for(size_t j=0; j<modesV.size(); j++)
            {
                if ( getDistance(distanceV[i], modesV[j]) < eps)
                {
                    is_found=true;
                    break;
                }
            }
            if (!is_found)
            {
                modesV.push_back(distanceV[i]);
            }
        }

        resWeightsV.resize(modesV.size());

        for (size_t i=0; i<modesV.size(); i++)
        {
            resWeightsV[i] = getResultWeight(modesV[i]);
        }
    }
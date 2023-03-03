#include "somm22.h"
#include "peq_module.h"

#include <map>
#include <fstream>
#include <sstream>
#include <list>

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void peqInit(const char *fname)
        {
            soProbe(301, "%s(\"%s\")\n", __func__, fname);

            std::ifstream peq_file(fname);
            if (!peq_file.is_open())
                throw Exception(ENOENT, __func__);

            std::string line;
            while (std::getline(peq_file, line)) {
                
                int i = 0;
                while(isspace(line[i])) i++;
                if (line[i] == '\0' || line[i] == '#') {
                    continue;
                }
                // parse the line and store the data in a PeqBlock structure
                std::istringstream iss(line);
                peq::PeqBlock block;

                std::string token;
                std::getline(iss, token, ';');
                block.pid = std::stoi(token);

                std::getline(iss, token, ';');
                block.arrivalTime = std::stoi(token);

                std::getline(iss, token, ';');
                block.duration = std::stoi(token);

                std::getline(iss, token, '\n');
                block.addrSpaceSize = std::stoul(token, 0, 16);

                Event n_event;
                n_event.eventTime = block.arrivalTime;
                n_event.eventType = ARRIVAL;
                n_event.pid = block.pid;

                // check if the pid is already in the peqable map
                // if it is, throw an exception
                std::list<Event>::iterator it;
                for(it = peq::peqlist.begin();it != peq::peqlist.end();++it){
                    if(it->pid == n_event.pid){
                    throw Exception(EEXIST, __func__);
                }
                }
                peq::peqlist.push_back(n_event);
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22


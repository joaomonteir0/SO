/*
 *  \author João Monteiro n.mec.: 102690
 */

#include "somm22.h"
#include "pct_module.h"

#include <map>
#include <fstream>
#include <sstream>
#include <regex>

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

         void pctInit(const char *fname) 
        {
            std::ifstream pct_file(fname);
            if (!pct_file.is_open())
                throw Exception(ENOENT, __func__);

            std::string line;
            while (std::getline(pct_file, line)) {
                
                int i = 0;

                while(isspace(line[i])) i++;
                if (line[i] == '\0' || line[i] == '#') {
                    continue;
                }
                
                // parse the line and store the data in a PCBlock structure
                std::istringstream iss(line);
                pct::PCBlock block;

                std::string token;
                std::getline(iss, token, ';');
                block.pid = std::stoi(token);

                std::getline(iss, token, ';');
                block.arrivalTime = std::stoi(token);

                std::getline(iss, token, ';');
                block.duration = std::stoi(token);

                std::getline(iss, token, '\n');
                /*std::regex r1("//s+");
                token = std::regex_replace(token, r1, "");

                std::regex r("0x");
                token = std::regex_replace(token, r, "");*/
                block.addrSpaceSize = std::stoul(token, 0, 16);

                block.memAddress = NULL;
                block.startTime = 9999;
                
                block.stateName = "";
                block.state = TO_COME;

                // check if the pid is already in the pctable map
                // if it is, throw an exception
                if (pct::pctable.find(block.pid) != pct::pctable.end()) {
                    throw Exception(EEXIST, __func__);
                }

                // insert the PCBlock into the pctable map
                pct::pctable[block.pid] = block;
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22


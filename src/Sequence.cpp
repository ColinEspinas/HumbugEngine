#include "HumbugEngine/Sequence.h"
#include <fstream>
#include <sstream>

#include <iostream>

Sequence::Sequence(std::string fname)
{
    // Open the file for reading
    std::ifstream fin(std::string("assets/animations/") + fname + ".heas");
    if (!fin) return;

    // Init
    int LastIndex = -1;
    tMethod = 0;
    tAxis = 0;
    for (int ii=0; ii<3; ++ii)
        for (int jj=0; jj<3; ++jj)
            for (int kk=0; kk<2; ++kk)
                saved_Config[ii][jj][kk] = false;

    // Read File
    std::string line;
    while (!fin.eof())
    {
        std::getline(fin, line);

        if (line.find("build ") == 0)
        {
            // Init & Verif
            line += " 0";
            std::vector<std::string> tContent; std::string tStr;
            std::stringstream ss(line.c_str() + 6);

            // Fill String Content
            do {
                ss >> tStr;
                tContent.push_back(tStr);
            } while (tStr != "0");
            tContent.pop_back();

            // Read each Content String
            for (std::string STR : tContent)
            {
                // Set Animation Method
                if (STR.find("T") == 0 || STR.find("t") == 0)
                    LastIndex = ComputeIndex(0, tAxis);
                else if (STR.find("R") == 0 || STR.find("r") == 0)
                    LastIndex = ComputeIndex(1, tAxis);
                else if (STR.find("S") == 0 || STR.find("s") == 0)
                    LastIndex = ComputeIndex(2, tAxis);
                
                // Set Animation Axis
                else if (STR.find("X") == 0 || STR.find("x") == 0)
                    LastIndex = ComputeIndex(tMethod, 0);
                else if (STR.find("Y") == 0 || STR.find("y") == 0)
                    LastIndex = ComputeIndex(tMethod, 1);
                else if (STR.find("Z") == 0 || STR.find("z") == 0)
                    LastIndex = ComputeIndex(tMethod, 2);
                
                // Set Config Boolean
                else if (STR.find("-L") == 0 || STR.find("-l") == 0)
                    saved_Config[tMethod][tAxis][0] = true;
                else if (STR.find("-S") == 0 || STR.find("-s") == 0)
                    saved_Config[tMethod][tAxis][1] = true;
            }
        }

        else if (LastIndex >= 0 && line[0] >= 48 && line[0] <= 57)
        {
            float t, v;
            std::stringstream ss(line.c_str());
            ss >> t >> v;
            saved_Keys[tMethod][tAxis].push_back({t,v});
        }
    }
}

void Sequence::Apply(std::shared_ptr<Animator> anim)
{
    for (int ii = 0; ii < 3; ++ii)
        for (int jj = 0; jj < 3; ++jj)
        {
            for (int kk = 0; kk < saved_Keys[ii][jj].size(); ++kk)
                anim->addKeyTo((AnimationType::METHOD)ii, (AnimationType::AXIS)jj,
                    saved_Keys[ii][jj][kk][0], saved_Keys[ii][jj][kk][1]);
            anim->getAnimation((AnimationType::METHOD)ii, (AnimationType::AXIS)jj)
                ->loop = saved_Config[ii][jj][0];
            anim->getAnimation((AnimationType::METHOD)ii, (AnimationType::AXIS)jj)
                ->smooth = saved_Config[ii][jj][1];
        }
    
    //for (int ii=0; ii<3; ++ii) for (int jj=0; jj<3; ++jj) std::cout<<"Loop: "<<saved_Config[ii][jj][0]<<" | Smooth: "<<saved_Config[ii][jj][1]<<std::endl; //DEBUG
}

int Sequence::ComputeIndex(int method, int axis)
{
    tMethod = method; tAxis = axis;
    return method * 3 + axis;
}
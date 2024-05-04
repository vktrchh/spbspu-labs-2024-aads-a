#include <iostream>
#include <fstream>

#include "getMaps.hpp"
#include "mapMaster.hpp"
#include "twoThreeTree.hpp"

int main(int argc, char *argv[])
{
  zhalilov::TwoThree < int, int > maps;
  maps.insert({10, 0});
  maps.insert({20, 0});
  maps.insert({60, 0});
  maps.insert({50, 0});
  maps.insert({40, 0});
  maps.erase(50);
  // zhalilov::TwoThree < std::string, zhalilov::primaryMap > maps;
  // if (argc == 2)
  // {
  //   std::ifstream file(argv[1]);
  //   zhalilov::getMaps(maps, file);
  // }
  // else
  // {
  //   std::cerr << "No file argument";
  //   return 1;
  // }
  //
  // zhalilov::MapMaster master(maps);
  // std::string cmdOutput;
  // while (!std::cin.eof())
  // {
  //   try
  //   {
  //     master.doCommandLine(std::cin, cmdOutput);
  //     if (!cmdOutput.empty())
  //     {
  //       std::cout << cmdOutput << '\n';
  //     }
  //   }
  //   catch (const std::invalid_argument &e)
  //   {
  //     std::cout << "<INVALID COMMAND>\n";
  //   }
  //   catch (const std::exception &e)
  //   {
  //     std::cerr << e.what();
  //     return 1;
  //   }
  // }
}

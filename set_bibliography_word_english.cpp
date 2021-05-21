#include <fstream>
#include <sstream>
#include <iostream>
#include "../python_like/split_strip.h"
#include "../python_like/in_operator.h"

int main(int argc, char *argv[])
{
  // This code works with .xml files created by JabRef
  using namespace pl_split_strip;
  #define in <in_operator::in>
  #define not_in <in_operator::not_in>

  if (argc != 2)
  {
  	std::cout << "This executable needs 1 argument: input xml file" << std::endl;
  	return 0;
  }
  if (".xml" not_in argv[1])
  {
  	std::cout << "This executable needs a file with extension xml" << std::endl;
  	return 0;
  }
  std::vector<std::string> nametok = split(argv[1], ".");
  nametok[nametok.size()-2] = nametok[nametok.size()-2] + "_english";

  std::string name = join(".", nametok);

  std::ifstream f_in(argv[1]);
  std::ofstream f_out(name);

  std::string line;
  while (std::getline(f_in, line))
  {
  	if ("<b:Source>" in line)
  	  line = line + "<b:LCID>1033</b:LCID>";
  	f_out << line << std::endl;
  }
  #undef in
  #undef not_in
  return 0;
}


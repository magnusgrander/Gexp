#include "parser.h"

int main()
{
  Parser parser;

  std::cout.precision(12);

  while (std::cin) {
	std::cout << "Enter an expression:\n";
    std::string s;
    std::getline(std::cin, s);
    if (!std::cin || s == "quit") break;
    if (!std::cin || s == "clear") 
    {
		parser.Clear();
	}
    
    try {
      std::cout << parser(s) << '\n';
    } catch(const Lexical_error& e) {
      std::cerr << "Lexical error: " << e << '\n';
    } catch(const Syntax_error& e) {
      std::cerr << "Syntax error: " << e << '\n';
    } catch(const Runtime_error& e) {
      std::cerr << "Runtime error: " << e << '\n';
    }
  }
}

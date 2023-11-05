#include "lexer.h"
#include <vector>

class Parser {
public:
  Parser();
  void Clear();
  double operator()(const std::string& s);
  int results;
  std::vector<double>value;

private:
  Lexer* p_lexer;
  std::map<std::string, double> symbol_table;  

  double assign_expr();
  double add_expr();
  double mul_expr();
  double pow_expr();
  double unary_expr();
  double primary();

  double get_argument();

  // Check for root of a negative number.
  static void check_domain(double x, double y);
};


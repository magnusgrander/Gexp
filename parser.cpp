#include "parser.h"

double to_number(const std::string& s)
{
  std::istringstream ist{s};
  ist.exceptions(std::ios_base::failbit);
  double x;
  ist >> x;
  return x;
}

std::string to_string(double x)
{
  std::ostringstream ost;
  ost << x;
  return ost.str();
}

Parser::Parser()
{
  symbol_table["pi"] = 4.0 * atan(1.0);
  symbol_table["e"] = exp(1.0);
}

void Parser::Clear()
{
  symbol_table.clear();	
  symbol_table["pi"] = 4.0 * atan(1.0);
  symbol_table["e"] = exp(1.0);
}

double Parser::operator()(const std::string& s)
{
  std::istringstream ist{s};
  p_lexer = new Lexer{ist};
  double result = assign_expr();
  delete p_lexer;
  return result;
}

double Parser::assign_expr()
{
  Token t = p_lexer->get_current_token();
  std::string text = p_lexer->get_token_text();

  double result = add_expr();

  if (p_lexer->get_current_token() == Token::Assign) {
    if (t != Token::Id)
      throw Syntax_error{"target of assignment must be an identifier"};

    if (text == "pi" || text == "e")
      throw Syntax_error{"attempt to modify the constant " + text};

    p_lexer->advance();
    return symbol_table[text] = add_expr();
  }

  return result;
}

double Parser::add_expr()
{
  double result = mul_expr();

  for (;;) {
    switch (p_lexer->get_current_token()) {
    case Token::Plus:
      p_lexer->advance();
      result += mul_expr();
      break;
    case Token::Minus:
      p_lexer->advance();
      result -= mul_expr();    
    default:
      return result;
    }
  }
}

double Parser::mul_expr()
{
  double result = pow_expr();
  double x;

  for (;;) {
    switch (p_lexer->get_current_token()) {
    case Token::Mul:
      p_lexer->advance();
      result *= pow_expr();
      break;
    case Token::Div:
      p_lexer->advance();
      x = pow_expr();
      if (x == 0)
        throw Runtime_error{"divide by zero"};
      result /= x;
      break;
    case Token::Mod:
      p_lexer->advance();
      x = pow_expr();
      if (x == 0)
        throw Runtime_error{"divide by zero"};
      result = fmod(result, x);
      break;
    default:
      return result;
    }
  }
}

double Parser::pow_expr()
{
  double result = unary_expr();

  if (p_lexer->get_current_token() == Token::Pow) {
    p_lexer->advance();
    double x = unary_expr();
    check_domain(result, x);
    return pow(result, x);
  }

  return result;
}

double Parser::unary_expr()
{
  switch (p_lexer->get_current_token()) {
  case Token::Plus:
    p_lexer->advance();
    return +primary();
  case Token::Minus:
    p_lexer->advance();
    return -primary();
  default:
    return primary();
  }
}

double Parser::primary()
{
  std::string text = p_lexer->get_token_text();
  double arg;

  switch (p_lexer->get_current_token()) {
  case Token::Id:
    p_lexer->advance();
    return symbol_table[text];
  case Token::Number:
    p_lexer->advance();
    return to_number(text);
  case Token::Lp:
    p_lexer->advance();
    arg = add_expr();
    if (p_lexer->get_current_token() != Token::Rp)
      throw Syntax_error{"missing )"};
    p_lexer->advance();
    return arg;
  case Token::Sin:
    return sin(get_argument());
  case Token::Cos:
    return cos(get_argument());
  case Token::Tan:
    return tan(get_argument());
  case Token::Asin:
    return asin(get_argument());
  case Token::Acos:
    return acos(get_argument());
  case Token::Atan:
    return atan(get_argument());
  case Token::Log:       
    return log(get_argument());
  case Token::Exp:
    return exp(get_argument());
  case Token::Log10:    
    return log10(get_argument());
  case Token::Exp10:
    return exp10(get_argument());
  case Token::Sqrt:    
    return sqrt(get_argument());
  case Token::Rnd:  
    arg = get_argument();
    return(rand() % int(arg)); 
  case Token::Round:    
    return round(get_argument());  
  case Token::Floor:    
    return floor(get_argument());
  case Token::Fabs:    
    return fabs(get_argument());
  case Token::Expm1:    
    return expm1(get_argument());
  case Token::Sinh:    
    return sqrt(get_argument());
  case Token::Tanh:    
    return tanh(get_argument());  
  case Token::Cbrt:    
    return cbrt(get_argument());      
  default:
    throw Syntax_error{"Expression error"};
  }
}

void Parser::check_domain(double x, double y)
{  
  if (x >= 0) return;
  double e = std::abs(y);
  if (e <= 0 || e >= 1) return;  
  throw Runtime_error{"attempt to take root of a negative number"};
}

double Parser::get_argument()
{  
  p_lexer->advance();
  if (p_lexer->get_current_token() != Token::Lp)
    throw Syntax_error{"missing ( after function name"};
  p_lexer->advance();
  double arg = add_expr();
  if (p_lexer->get_current_token() != Token::Rp)
    throw Syntax_error{"missing ) after function argument"};
  p_lexer->advance();
  return arg;
}

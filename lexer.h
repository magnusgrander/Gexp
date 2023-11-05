#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>

template<int N>
  class Error {
  public:
    explicit Error(const std::string s) : message{s} { }

    std::string get_message() const { return message; }
    void put(std::ostream& os) const { os << message; }

  private:
    std::string message;
  };

using Lexical_error = Error<1>;
using Syntax_error = Error<2>;
using Runtime_error = Error<3>;

template<int N>
  std::ostream& operator<<(std::ostream& os, const Error<N>& e)
  {
    e.put(os);
    return os;
  }

// The basic elements of our expressions.
enum class Token {
  Id, Number, Sin, Cos, Tan, Asin, Acos, Atan, Log, Exp, Rnd,
  Round, Floor, Fabs, Expm1, Sinh, Tanh , Cbrt, 
  Log10, Exp10, Sqrt, Assign='=', Plus='+', Minus='-', cma=',',
  Mul='*', Div='/', Mod='%', Pow='^', Lp='(', Rp=')', Eofsym=-1
};

class Lexer {
public:
  explicit Lexer(std::istream& is);
  explicit Lexer(std::istream* ps);

  Lexer(const Lexer&) = delete;
  Lexer& operator=(const Lexer&) = delete;

  Lexer(Lexer&&) = delete;
  Lexer& operator=(Lexer&&) = delete;

  ~Lexer() { if (owns_input) delete p_input; }

  Token get_current_token() const { return current_token; }
  std::string get_token_text() const { return current_token_text; }

  void advance();		// Read the next token in the stream.

private:
  std::istream* p_input;		// The source stream (a stream of characters).
  bool owns_input;			// True if we can delete p_input, false if we can't.

  Token current_token;
  std::string current_token_text;

  void init();				

  Token get_token();			
  std::string token_buffer;		// The text of the token that get_token() just found.

  void exponent_part(char& c);		// A helper function for get_token() when it is looking for a number.
};



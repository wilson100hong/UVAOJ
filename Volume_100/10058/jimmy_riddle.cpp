// NOTE:
// 1. size_t - 1 is dangerout. when size_t == 0.
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
using namespace std;

constexpr char kOk[] = "YES I WILL";
constexpr char kError[] = "NO I WON'T";

set<string> NOUNS = {
  "tom",
  "jerry",
  "goofy",
  "mickey",
  "jimmy",
  "dog",
  "cat",
  "mouse"
};

set<string> VERBS = {
  "hate", "hates",
  "love", "loves",
  "know", "knows",
  "like", "likes"
};

set<string> ARTICLES = {
  "a",
  "the"
};

enum class Token {
  COMMA = 0,  // ","
  AND,  // "and"
  ARTICLE,  // "a" | "the
  NOUN,
  VERB
};

string TokenToStr(const Token& token) {
  switch(token) {
    case Token::COMMA:
      return "COMMA";
    case Token::AND:
      return "AND";
    case Token::ARTICLE:
      return "ARTICLE";
    case Token::NOUN:
      return "NOUN";
    case Token::VERB:
      return "VERB";
  }
}


bool ParseActiveList(const vector<Token>& tokens, int* i);
bool ParseAction(const vector<Token>& tokens, int* i);
bool ParseStatement(const vector<Token>& tokens, int* i);

bool ParseActor(const vector<Token>& tokens, int* i) {
  int index = *i;
  if (index < tokens.size() &&
      tokens[index] == Token::NOUN) {
    (*i)++;
    return true;
  } else if (
      index + 1 < tokens.size() &&
      tokens[index] == Token::ARTICLE &&
      tokens[index+1] == Token::NOUN) {
    *i = *i + 2;
    return true;
  }
  return false;
}

bool ParseActiveList(const vector<Token>& tokens, int* i) {
  if (!ParseActor(tokens, i)) {
    return false;
  }
  if (*i < tokens.size() && tokens[*i] == Token::AND) {
    (*i)++;  // Skip AND
    return ParseActiveList(tokens, i);
  }
  return true;
}

bool ParseAction(const vector<Token>& tokens, int* i) {
  if (!ParseActiveList(tokens, i)) {
    return false;
  }

  if (*i >= tokens.size() || tokens[*i] != Token::VERB) {
    return false;
  }
  (*i)++;  // Skip VERB

  return ParseActiveList(tokens, i);
}

bool ParseStatement(const vector<Token>& tokens, int* i) {
  if (!ParseAction(tokens, i)) {
    return false;
  }
  if (*i < tokens.size() && tokens[*i] == Token::COMMA) {
    (*i)++;  // Skip COMMA
    return ParseStatement(tokens, i); 
  }
  return (*i) == tokens.size();
}

vector<string> Split(const string& words) {
  // Split on ',', but still keep in result.
  // Assume no spaces in between.
  vector<string> res;

  int i = 0, j = 0;
  while (j < words.size()) {
    if (words[j] == ',') {
      if (j!=i) {
        res.push_back(words.substr(i, j-i));
      }
      res.push_back(",");  // words[j] itself
      j++;
      i = j;
    } else {
      j++;
    }
  }
  
  if (j!=i) {
    res.push_back(words.substr(i, j-i));
  }
  return res;
}

string Solve(const string& str) {
  stringstream ss(str);
  vector<Token> tokens;
  string temp;
  while (ss >> temp) {
    // Split on ','
    vector<string> words = Split(temp);
    for (const auto& word : words) {
      if (NOUNS.count(word)) {
        tokens.push_back(Token::NOUN);
      } else if (VERBS.count(word)) {
        tokens.push_back(Token::VERB);
      } else if (ARTICLES.count(word)) {
        tokens.push_back(Token::ARTICLE);
      } else if (word == ",") {
        tokens.push_back(Token::COMMA);
      } else if (word == "and") {
        tokens.push_back(Token::AND);
      } else {
        return kError;
      }
    }
  }


  int i = 0;
  if (ParseStatement(tokens, &i)) {
    return kOk;
  } else {
    return kError;
  }
}

int main() {
  string line;
  int i = 1;
  while (getline(cin, line)) {
    cout << Solve(line) << endl;
  }
}

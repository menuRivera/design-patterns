/*
You are given a class called Sentence , which takes a string such as "hello
world". You need to provide an interface such that the indexer (operator [] )
returns a WordToken  that can be used to capitalize a particular word in the
sentence.

Typical use would be something like:

    Sentence sentence("hello world");
    sentence[1].capitalize = true;
    cout << sentence.str(); // prints "hello WORLD"
*/
#include <cctype>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Basic splitting function for strings
 */
vector<string> split(const string &str, char delim) {
  vector<string> tokens;
  stringstream ss(str);
  string token;
  while (getline(ss, token, delim)) {
    tokens.push_back(token);
  }
  return tokens;
}

struct Sentence {

  Sentence(const string &text) : text(text) {
    for (const string &word : split(text, ' ')) {
      words.emplace_back(WordToken{word});
    }
  }

  struct WordToken {
    string word;
    bool capitalize;

    WordToken(const string &word) : word(word), capitalize(false) {}

    string get_word() {
      if (!capitalize)
        return word;

      string s = word;

      for (char &c : s) {
        c = toupper(c);
      }

      return s;
    }
  };

  WordToken &operator[](size_t index) { return words[index]; }

  string str() const {
    ostringstream oss;

    for (WordToken w : words) {
      oss << w.get_word() << " ";
    }
    return oss.str();
  }

private:
  string text;
  vector<WordToken> words;
};

int main() {
  Sentence sentence("hello world dangggg");
  sentence[1].capitalize = true;
  cout << sentence.str() << endl;
}

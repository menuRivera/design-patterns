/**
 * Avoid stuffing too much into a single interface
 */

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Document;
/**
 * Example of a rather bad approach, as IMachine is probably doing too much
 */
// struct IMachine {
//   virtual void print(Document &doc) = 0;
//   virtual void scan(Document &doc) = 0;
//   virtual void fax(Document &doc) = 0;
// };
//
// struct Multifunctional : IMachine {
//   void print(Document &doc) override {}
//   void scan(Document &doc) override {}
//   void fax(Document &doc) override {}
// };
//
// struct Scanner : IMachine {
//	  // what should print() and fax() do?
//   void print(Document &doc) override {}
//   void scan(Document &doc) override {
// 	  // ok
//   }
//   void fax(Document &doc) override {}
// };

struct IPrinter {
  virtual void print(Document &doc) = 0;
};
struct IScanner {
  virtual void scan(Document &doc) = 0;
};
struct IFax {
  virtual void fax(Document &doc) = 0;
};

struct Printer : IPrinter {
  void print(Document &doc) override {}
};
struct Scanner : IScanner {
  void scan(Document &doc) override {}
};

// struct IMachine : IPrinter, IScanner {}; //why?

struct Multifunctional : IPrinter, IScanner {
  IPrinter &printer;
  IScanner &scanner;

  Multifunctional(IPrinter &printer, IScanner &scanner)
      : printer(printer), scanner(scanner) {}

  void print(Document &doc) override { printer.print(doc); }
  void scan(Document &doc) override { scanner.scan(doc); }
};

int main() { return 0; }

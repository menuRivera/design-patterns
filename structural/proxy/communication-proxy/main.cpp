#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <iostream>
#include <string>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

using namespace std;

struct Pingable {
  virtual string ping(const string &msg) = 0;
};

struct Pong : Pingable {
  string ping(const string &msg) override { return msg + " pong"; }
};

struct RemotePong : Pingable {
  /**
   * Makes an http request to the server (./server/main.cpp)
   */
  string ping(const string &msg) override {
    string result;
    http_client client(U("http://localhost:8080/"));
    uri_builder builder(U("/ping"));

    builder.append_query(U("msg"), U(msg));

    pplx::task task =
        client.request(methods::GET, builder.to_string())
            .then([=](http_response res) { return res.extract_string(); });

    task.wait();
    return task.get();
  }
};

void tryit(Pingable &pp) { cout << pp.ping("ping") << endl; };

int main() {
  // they do exactly the same here, but in a completly different way in the
  // underlying logic

  // Pong pp;
  RemotePong pp;
  cout << pp.ping("test") << endl;

  for (size_t i = 0; i < 3; i++) {
    tryit(pp);
  }
}

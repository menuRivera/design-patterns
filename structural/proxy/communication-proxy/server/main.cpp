#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <exception>
#include <iostream>
#include <map>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http;
using namespace web::http::experimental::listener;

int main() {
  uri_builder uri(U("http://localhost:8080/ping"));

  http_listener listener(uri.to_string());

  listener.support(methods::GET, [](http_request req) {
    cout << "Received GET request" << endl;

    auto query = req.request_uri().query();
    auto params = req.request_uri().split_query(query);

    string res = params["msg"] + " pong";

    cout << res << endl;

    req.reply(status_codes::OK, res);
  });

  try {
    listener.open().wait();

    cout << "Server listening on port 8080" << endl;

    // keep the server running until a key is pressed
    cin.get();

    listener.close().wait();

    cout << "Server closed" << endl;

  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }

  return 0;
}

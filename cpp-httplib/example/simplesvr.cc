//
//  simplesvr.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <cstdio>
#include <httplib.h>
#include <iostream>
#include <jsoncpp/json/json.h> 
#include "base64.h"

using namespace httplib;
using namespace std;
using namespace dev;

Json::Value dump_body(std::string data) {
  Json::Reader reader;  
  Json::Value root;  

  Json::Value out;
  if (reader.parse(data, root)) 
  {  
   std::string img_base64 = root["image"].asString(); 
   std::string img_encode = dev::base64_decode(img_base64);
   std::cout << img_encode << std::endl;
   out["img_encode"] = img_encode;
  }  

  return out;
}


int main(int argc, const char **argv) {
  if (argc > 1 && string("--help") == argv[1]) {
    cout << "usage: simplesvr [PORT] [DIR]" << endl;
    return 1;
  }

  Server svr;

  svr.Post("/multipart", [](const Request &req, Response &res) {
    auto body = dump_body(req.body);
    res.set_content(body.toStyledString(), "application/json");
  });

  auto port = 8080;
  if (argc > 1) { port = atoi(argv[1]); }

  cout << "The server started at port " << port << "..." << endl;

  svr.listen("0.0.0.0", port);

  return 0;
}

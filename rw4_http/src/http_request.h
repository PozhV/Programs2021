/*
 * http_request.h
 *
 *  Created on: 7 окт. 2021 г.
 *      Author: User
 */
#pragma once
#include <string_view>
using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};

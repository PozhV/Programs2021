/*
 * http_request.h
 *
 *  Created on: 7 ���. 2021 �.
 *      Author: User
 */
#pragma once
#include <string_view>
using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};

/*
 * stats.h
 *
 *  Created on: 7 окт. 2021 г.
 *      Author: User
 */
#include "http_request.h"
#include<iostream>
#include<vector>
#pragma once
#include <string_view>

#include <map>
using namespace std;
class Stats {
public:
	Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
  vector<string_view> methods_v;
  vector<string_view> uris_v;
  vector<string> methods;
  vector<string> uris;
  map<string_view, int> u_count;
  map<string_view, int> m_count;
};

HttpRequest ParseRequest(string_view line);


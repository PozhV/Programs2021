/*
 * stats.cpp
 *
 *  Created on: 8 окт. 2021 г.
 *      Author: User
 */
#include"stats.h"
void Print(const map<string_view, int>& m)
{
	for(auto it: m)
		cout<<it.first<<" "<<it.second<<endl;
}
Stats::Stats(){
	  methods = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
	  uris = {"/", "/order", "/product", "/basket", "/help", "unknown"};
		for(size_t i = 0; i < methods.size(); i++)
		{
			methods_v.push_back(methods[i]);
			m_count.insert(make_pair(methods_v[i], 0));
		}

		for(size_t i = 0; i < uris.size(); i++)
		{
			uris_v.push_back(uris[i]);
			u_count.insert(make_pair(uris_v[i], 0));
		}
	}
  void Stats::AddMethod(string_view method){
	  if(m_count.count(method) == 0) method = methods[4];
	  m_count[method]++;
	  //Print(m_count);
  }
  void Stats::AddUri(string_view uri){
	  if(u_count.count(uri) == 0) uri = uris[5];
	  u_count[uri]++;
	  //Print(u_count);
  }
  const map<string_view, int>& Stats::GetMethodStats() const{
	  return m_count;
  }
  const map<string_view, int>& Stats::GetUriStats() const{
	  return u_count;
  }
HttpRequest ParseRequest(string_view line)
{
	HttpRequest req;
	size_t pos = 0, pos_ = line.find_first_not_of(' ' , 0);
	if(pos_ == line.npos)
	{
		req.method = line;
		req.uri = "";
		req.protocol = "";
	}
	else
	{
	pos = line.find_first_of(' ', pos_);
	if(pos == line.npos)
	{
		req.method = line;
		req.uri = "";
		req.protocol = "";
	}
	else{
	req.method = line.substr(pos_, pos - pos_);
	//cout<<req.method<<endl;
	pos_ = line.find_first_not_of(' ', pos);
	pos = line.find_first_of(' ', pos_);
	if(pos_ == line.npos)
	{
		//cout<<pos<<" "<<line.size() - pos_ - 1<<endl;
		req.uri = line.substr(pos, line.size() - pos - 1);
		req.protocol = "";
	}
	else if(pos == line.npos)
	{
		cout<<pos_<<" "<<line.size() - pos_ - 1<<endl;
		req.uri = line.substr(pos_, line.size() - pos_ - 1);
		req.protocol = "";
	}
	else
	{
	req.uri = line.substr(pos_, pos - pos_);
	req.protocol = line.substr(pos + 1, line.npos - pos);
	}
	}
	}
	return req;
}


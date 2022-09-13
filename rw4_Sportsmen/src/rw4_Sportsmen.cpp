//============================================================================
// Name        : rw4_Sportsmen.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include<list>
#include<iterator>
using namespace std;

int main() {
	unordered_map<uint32_t, list<uint32_t>::iterator> Sp_places;
	list<uint32_t> Sportsmen;
	uint32_t count;
	cin>>count;
	for(uint32_t i = 0; i < count; i++)
	{
		uint32_t sportsman, place;
		cin>>sportsman>>place;
		if(Sp_places.count(place) == 0)
		{
			Sportsmen.push_back(sportsman);
			auto it = Sportsmen.end();
			it--;
			Sp_places[sportsman] = it;
		}
		else{
			auto it = Sportsmen.insert(Sp_places[place], sportsman);
			Sp_places[sportsman] = it;
		}
	}
	for(auto it = Sportsmen.begin(); it != Sportsmen.end(); it++)
	{
		cout<<*it<<endl;
	}
	return 0;
}

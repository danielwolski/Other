#pragma once
#include <iostream>

using namespace std;

class Commentator
{
public:
	static void add_comment(string komentarz);
	static void comment();
	static void clear_comment();
protected:
	static string text;
};

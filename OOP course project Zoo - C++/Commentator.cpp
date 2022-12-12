#include "Commentator.h"

string Commentator::text = "";

void Commentator::add_comment(string comment)
{
	text += comment + "\n";
}

void Commentator::comment()
{
	if (text == "")
		return;
	cout << text;
}

void Commentator::clear_comment()
{
	text = "";
}

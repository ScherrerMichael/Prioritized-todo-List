// Michael Scherrer
// CS202 - programming systems
// Portland State university
// Program 3 - priority organizer
//  -- MAIN -- 

#include "Tree.h"

using namespace std;

void write(int num);
int read();

void clear(int num_lines);
void clear(int begin, int end);
void response(char &response);
void response(int &reponse);
void response(String &response);

int main()
{
	clear(100);

	cout<< "Priority Organiser" <<endl;

	Tree tree;

	char char_response;
	int num_response;
	String string_response;
	String notification = " ";


	do
	{
		cout<<"0) Create new \n1) Load from file";
		clear(10);
		cout<<"Enter input:";
		response(num_response);

		if(num_response == 1)
		{
			do
			{

				clear(100);
				cout<<"Here are some .txt files in the directory: ";
				cout<<endl;
				tree.show_file_list();
				cout<<endl;
				clear(10);
				cout<<"Please specify which file to load: ";
				response(string_response);
				cout<<endl;
				cout<<"you entered: " << string_response <<" is this correct? (y/n/q): ";
				response(char_response);

			}while(char_response != 'Y' && char_response != 'Q');
		}
		else // create new
		{
			cout<<"Title of new List: ";
			response(string_response);
			tree.set_title(string_response);
		}

		if(char_response == 'Y')
		{
			tree.load(string_response);
		}

		if(char_response != 'Q')
		{


			do
			{
				clear(100);
				cout<< notification <<endl;
				tree.display();
				clear(10);
				cout<<"0) Filter by name\n1) Filter by subject\n2) Add item\n3) Remove by name\n4) Save \n5) Quit \n";
				cout<<"Enter input: ";
				response(num_response);

				if(num_response == 0) //filter by name
				{
					cout<<"Enter name to search: ";
					response(string_response);
					clear(100);
					tree.display_names(string_response);
					clear(10);
					cout<<"Enter anything go back: ";
					response(char_response);
				}
				else if(num_response == 1) // fiter by subject
				{
					cout<<"Enter subject to search: ";
					response(string_response);
					clear(100);
					tree.display_subjects(string_response);
					clear(10);
					cout<<"Enter anything go back: ";
					response(char_response);
				}
				else if(num_response == 2) //add item
				{
					Item to_add;

					cout<<endl;
					cout<<"Enter name: ";
					response(string_response);
					to_add.set_name(string_response);

					cout<<"Enter subject: ";
					response(string_response);
					to_add.set_subject(string_response);

					cout<<"Enter Url: ";
					response(string_response);
					to_add.set_url(string_response);

					cout<<"Enter priority: ";
					response(num_response);
					to_add.set_priority(num_response);
					num_response = -1;

					tree.add(to_add);
				}
				else if(num_response == 3) // remove item by name
				{
					cout<<"Enter item name to remove: ";
					response(string_response);
					tree.remove(string_response);

				}
				else if(num_response == 4) // save
				{
					tree.save();
					notification = "Save Successful!";
				}
				else if(num_response == 5) // quit
				{
					clear(100);
					cout<<"Goodbye!"<<endl;
					clear(10);
				}

			}while(num_response != 5);

		}


	}while(char_response != 'Q' && num_response!= 5);


	return 0;
}

void response(char &response)
{
	cin >> response;
	cin.ignore(100, '\n');
	response = toupper(response);
}

void response(int &response)
{
	cin >> response;
	cin.ignore(100, '\n');
}

void response(String &response)
{
	cin >> response;
	cin.ignore(100, '\n');
}

void clear(int num_lines)
{
	clear(0, num_lines);
}

void clear(int begin, int end)
{
	if(begin == end)
		return;

	cout<<endl;

	return clear(++begin, end);
}



bool operator==(const Item& a, const Item& b)
{
	return (a.name == b.name && a.priority == b.priority);
}

bool operator!=(const Item& a, const Item& b)
{
	return (a.name != b.name && a.priority != b.priority);
}

bool operator<(const Item& a, const Item& b)
{
	return (a.priority > b.priority);
}

bool operator>(const Item& a, const Item& b)
{
	return (a.priority < b.priority);
}

bool operator<=(const Item& a, const Item& b)
{
	return (a.priority <= b.priority);
}

bool operator>=(const Item& a, const Item& b)
{
	return (a.priority <= b.priority);
}






// == //

bool operator==(const String& a, const String &b)
{
	return strcmp(a.text,b.text) == 0;

}


bool operator==(const String& a, const char* &b)
{
	return strcmp(a.text,b) == 0;

}

bool operator==(const char* &a, const String &b)
{
	return strcmp(a,b.text) == 0;

}



// != //

bool operator!=(const String& a, const String &b)
{
	return strcmp(a.text,b.text) != 0;

}


bool operator!=(const String& a, const char* &b)
{
	return strcmp(a.text,b) != 0;

}

bool operator!=(const char* &a, const String &b)
{
	return strcmp(a,b.text) != 0;

}



// < //

bool operator<(const String& a, const String &b)
{
	return strcmp(a.text,b.text) <  0;

}


bool operator<(const String& a, const char* &b)
{
	return strcmp(a.text,b) < 0;

}

bool operator<(const char* &a, const String &b)
{
	return strcmp(a,b.text) < 0;

}


// > //

bool operator>(const String& a, const String &b)
{
	return strcmp(a.text,b.text) >  0;

}


bool operator>(const String& a, const char* &b)
{
	return strcmp(a.text,b) > 0;

}

bool operator>(const char* &a, const String &b)
{
	return strcmp(a,b.text) > 0;

}



istream& operator>>(istream &in, String &s)
{
	char temp[200];
	in.get(temp, 200);
	s.length = strlen(temp);
	s.text = new char[strlen(temp) + 1];
	strcpy(s.text, temp);
	return in;
}

ostream& operator<<(ostream &o, const String &s)
{
	o << s.text;
	return o;
}




String operator+(const String& a, const String& b)
{
	char* temp = new char[a.length + b.length + 1];
	strcpy(temp, a.text);
	strcat(temp, b.text);
	return String(temp);
}

String operator+(const String& a, const char* &b)
{
	char* temp = new char[a.length + strlen(b) + 1];
	strcpy(temp, a.text);
	strcat(temp, b);
	return String(temp);
}

String operator+(const char* a, const String& b)
{
	char* temp = new char[strlen(a) + b.length + 1];
	strcpy(temp, a);
	strcat(temp, b.text);
	return String(temp);
}

ostream& operator<<(ostream& out, const Item &source)
{
	out << source.name <<"," << source.subject <<"," <<source.url <<"," << source.priority;

	return out;
}















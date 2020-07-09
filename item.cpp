// Michael Scherrer
// CS202 - programming systems
// Portland State university
// Program 3
//  -- String and Item classes-- 

#include"item.h"

			////////////
			// String //
			////////////

String::String()
{
	text = 0;
	length = 0;
}

String::~String()
{
	if(text)
	{
		delete[] text;
		text = 0;
		length = 0;
	}

}

String::String(const String &source)
{
	set_text(source);
}

String::String(const char* source)
{
	set_text(source);
}

int String::compare(const String &to_compare)
{
	return strcmp(this -> text, to_compare.text);
}

int String::compare(const char* &to_compare)
{
	return strcmp(this -> text, to_compare);
}

int String::set_text(const char* source)
{
	text = new char[strlen(source) + 1];
	
	strcpy(text, source);

	length = strlen(text);

	return length;
}

int String::set_text(const String &source)
{
	text = new char[strlen(source.text) + 1];
	
	strcpy(text, source.text);

	length = strlen(text);

	return length;
}

int String::set_text(const char letter)
{
	if(text) delete[] text;

	text = new char[1];

	text[0] = letter; text[1] = '\0';
	
	length = 1;

	return length;

}

int String::append(const String & source)
{
	if(!text)
	{
		set_text(source);
		return length;
	}

	char* temp = new char[strlen(text) + 1];
	strcpy(temp, text);

	delete[] text;

	text = new char[strlen(temp) + source.length];
	
	strcpy(text, temp);
	strcat(text, source.text);

	length += source.length;

	return length;
}

int String::append(const char* source)
{
	if(!text)
	{
		set_text(source);
		return length;
	}

	char* temp = new char[strlen(text) + 1];
	strcpy(temp, text);

	delete[] text;

	text = new char[strlen(temp) + strlen(source) + 1];
	
	strcpy(text, temp);
	strcat(text, source);

	length += strlen(source);

	return length;
}

int String::append(const char letter)
{
	if(!text)
	{
		set_text(letter);
		return length;
	}
	
	char* temp = new char[strlen(text) + 1];
	strcpy(temp, text);

	delete[] text;

	text = new char[strlen(temp) + 2];

	strcpy(text, temp);

	text[strlen(temp)] = letter;

	text[strlen(temp)+1] = '\0';

	++length;

	return length;
}

int String::append_spaces(int num)
{
	if(num == 0)
		return 0;

	append(' ');

	return append_spaces(--num) + 1;
}
bool String::contains(const String& string)
{
	return contains(string, length);
}

bool String::contains(const String &string, int end)
{
	if(end == 0)
		return false;

	String temp;
	
	substring(temp, 0, end);

	if(string == temp)
		return true;

	return contains(string, --end);
}

int String::index_of(const char letter, int start) const
{
	if(start >= length) // if character not found
		return -1;

	if(text[start] == letter)
		return start;

	return index_of(letter, ++start);
}

void String::substring(char* &arr, int begin, int end) const
{
	if(begin == end)
		return;

	String temp;

	temp.append(text[begin]);

	strcat(arr, temp.text);

	return substring(arr, ++begin, end);
}

void String::substring(String &result, int begin, int end) const
{
	if(begin == end)
		return;

	result.append(this -> text[begin]);

	return substring(result, ++begin, end);
}

void String::display()
{
	cout << text;
}

void String::display(int max)
{
	String alt;

	if(length < max)
	{
		this -> substring(alt, 0, length);
		alt.append_spaces(max - alt.length);
	}
	else
		this -> substring(alt, 0, max);

	cout << alt;
}

String& String::operator=(const String &source)
{
	if(this != &source)
	{
		if(this -> text)
			delete[] text;
		text = new char[source.length + 1];
		strcpy(text, source.text);
		length = source.length;
	}
	return *this;
}

String& String::operator=(const char* &source)
{
	if(this -> text)
		delete[] text;
	text = new char[strlen(source) + 1];
	strcpy(this -> text, source);
	length = strlen(source);

	return *this;
}

String& String::operator+=(const String &to_add)
{
	this -> append(to_add);
	return *this;
}

String& String::operator+=(const char* &to_add)
{
	this -> append(to_add);
	return *this;
}

char& String::operator[](int index) const
{
	return text[index];
}

int String::get_length()const
{
	return length;
}


			////////////
			// Item   //
			////////////


Item::Item()
{

}

Item::Item(const Item &to_copy)
{
	name = to_copy.name;
	subject = to_copy.subject;
	url = to_copy.url;
	priority = to_copy.priority;
}

Item::Item(const String& name, const String& subject, const String& url, int priority)
{
	this -> name = name;
	this -> subject = subject;
	this -> url = url;
	this -> priority = priority;
}	

Item::~Item()
{
	priority = -1;
}

int Item::set_name(String& name)
{
	this -> name = name;
	return 1;
}

int Item::set_name(const char* name)
{
	this -> name = name;
	return 1;
}

bool Item::contains_name(const String &search)
{
	return name.contains(search);
}

bool Item::match_name(const String &name)
{
	return this -> name == name;
}

int Item::set_subject(String& subject)
{
	this -> subject = subject;
	return 1;
}

int Item::set_subject(const char* subject)
{
	this -> subject = subject;
	return 1;
}

bool Item::contains_subject(const String &search)
{
	return subject.contains(search);
}

bool Item::match_subject(const String &subject)
{
	return this -> subject == subject;
}

int Item::set_url(String& url)
{
	this -> url = url;
	return 1;
}

int Item::set_url(const char* url)
{
	this -> url = url;
	return 1;
}

int Item::set_priority(int priority)
{
	this -> priority = priority;
	return 1;
}


int Item::set(const String& name, const String& subject, const String& url, int priority)
{
	this -> name = name;
	this -> subject = subject;
	this -> url = url;
	this -> priority = priority;

	return 1;
}

int Item::parse_item(const String &string)
{
	bool success = false;

	int name_comma = string.index_of(',', 0);

	int subject_comma = string.index_of(',', name_comma + 1);

	int url_comma = string.index_of(',', subject_comma + 1);

	char* to_convert = new char[string.get_length() - url_comma];

	to_convert[0] = '\0';

	if(name_comma != -1 && subject_comma != -1 &&  url_comma != -1)
	{

		string.substring(name, 0, name_comma); 

		string.substring(subject, name_comma + 1, subject_comma);

		string.substring(url, subject_comma + 1, url_comma);

		string.substring(to_convert, url_comma + 1, string.get_length());

		priority = atoi (to_convert);

		success = true;
	}


	return success;
}

Item& Item::operator=(const Item& source)
{
	if(this != &source)
	{
		this -> name = source.name;
		this -> subject = source.subject;
		this -> url = source.url;
		this -> priority = source.priority;
	}
	return *this;
}

char& Item::operator[](int index)
{
	return name[index];
}

void Item::display()
{
	cout<< "name: " << name << ", subject: " << subject << ", url: " << url << ", priority: " << priority <<endl;
}

void Item::display(int max)
{
	name.display(max); cout<< " | "; subject.display(max); cout<< " | "; url.display(max); cout<< " | " << priority; cout<<endl;
}

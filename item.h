// Michael Scherrer
// CS202 - programming systems
// Portland State university
// Program 3
//  -- item header -- 

#include<cstring>
#include<iostream>
#include<cctype>
using namespace std;

class String
{
	public:
		String();
		~String();

		String(const String &source);
		String(const char* source);

		int compare(const String & to_compare);
		int compare(const char* &to_compare);

		int set_text(const String &a_String);
		int set_text(const char* text);
		int set_text(const char letter);

		int index_of(const char letter, int start)const; // return the character at a given index

		bool contains(const String& string);		 // determine if the string is within current string.
								 // progresses backwards from end of string, and compares until match.

		int append(const String &to_add);
		int append(const char* to_add);
		int append(const char letter);
		int append_spaces(int num);

		String& substring(int begin, int end)const;
		void substring(char* &arr, int begin, int end) const;
		void substring(String &result, int begin, int end)const;

		void display();
		void display(int max);

		String& operator=(const char* &source);
		String& operator=(const String &source);

		friend String operator+(const String &a, const String &b);
		friend String operator+(const char* a, const String &b);
		friend String operator+(const String &a, const char* &b);

		String& operator+=(const String &source);
		String& operator+=(const char* &source);

		friend bool operator==(const String& a, const String& b);
		friend bool operator==(const String& a, const char* &b);
		friend bool operator==(const char* &a, const String& b);

		friend bool operator!=(const String& a, const String& b);
		friend bool operator!=(const String& a, const char* &b);
		friend bool operator!=(const char* &a, const String& b);

		friend bool operator<(const String& a, const String& b);
		friend bool operator<(const String& a, const char* &b);
		friend bool operator<(const char* &a, const String& b);

		friend bool operator>(const String& a, const String& b);
		friend bool operator>(const String& a, const char* &b);
		friend bool operator>(const char* &a, const String& b);

		friend istream& operator>>(istream &is, String& string);

		friend ostream& operator<<(ostream &o, const String &string);

		char& operator[](int index) const;

		int get_length()const;

	protected:
	private:
		bool contains(const String &string, int end);
		char* text;
		int length;
};

class Item
{
	public:
		Item();
		Item(const Item& to_copy);
		Item(const String& name, const String& subject,
				const String& url, int priority);
		~Item();
		int set_name(String& name);
		int set_name(const char* name);
		bool match_name(const String &name);
		bool contains_name(const String &search);

		int set_subject(String& subject);
		int set_subject(const char* subject);
		bool match_subject(const String &name);
		bool contains_subject(const String &search);

		int set_url(String& url);
		int set_url(const char* url);

		int set_priority(int priority);

		int set(const String& name, const String& subject, const String& url, int priority);

		int parse_item(const String &string); // parses the string row from file and creates an item out of it.

		Item& operator=(const Item& source);
		friend bool operator==(const Item& a, const Item& b); // compare priority
		friend bool operator!=(const Item& a, const Item& b); // then name
		friend bool operator<(const Item& a, const Item& b);  // |
		friend bool operator>(const Item& a, const Item& b);  // v
		friend bool operator<=(const Item& a, const Item& b);  // |
		friend bool operator>=(const Item& a, const Item& b);  // v


		friend ostream& operator<<(ostream& out, const Item &source);

		char& operator[](int index);

		void display();

		void display(int max);

	protected:
		String name;
		String subject;
		String url;
		int priority;
	private:
};


// Michael Scherrer
// CS202 - programming systems
// Portland State university
// Program 3
//  -- database header -- 

#include "item.h"

class Array // Note: this is similar to an ArrayList in java
{
	public:
		Array();
		Array(const Array& array);
		Array(Item** Items);
		~Array();

		int add(const Item &to_add); // Addts item. 
					     //if the size of the array is reached, double the size and copy
					     
		int remove(int index);       // Remove item at index. does not resize array.
		int remove_all();

		Item& operator[](int index);

		int get_size()const;	     // returns the current allocated size.
		int get_num_items()const;    // returns the number of elements in array.

	protected:
	private:
		int expand(Item** &dest, Item** source, int begin, int end);
		int add(Item** &items,const Item &to_add, int begin);

		void allocate(int begin);
		void copy(Item** &dest, Item** source, int begin, int size);
		int remove_all(int begin);

		Item** items;
		int size;
		int num_items;
};

class Database
{
	public:
		Database();
		Database(const String &file_name);
		~Database();

		int load(const String &file_name);	// load items from a .txt file
		int save(const String &file_name);	// write contents of database into file.
		void show_file_list();			// display all .txt files in current working directory.
		void display();				

	protected:
		Array array;
	private:
		int save(ofstream& file_out, int begin);
		void display(int begin);
};

class node: public Item
{
	public:
		node();
		node(const node &source);
		node(const Item &item);
		~node();

		node*& go_left();
		node*& go_right();

		void set_left(node* new_node);
		void set_right(node* new_node);

	protected:
		node* left;
		node* right;
	private:
};

class Tree: public Database
{
	public:
		Tree();
		Tree(const String &name);
		Tree(const Tree &source);
		~Tree();

		int add(const Item &item);
		int remove(const String &name);
		int remove_all();

		int display_subjects(const String &search);
		int display_names(const String &search);

		int load(const String &file_name);
		int save();

		void set_title(const String& title);
		void display();
	protected:
	private:
		String title;
		Item header_top;
		Item header_bottom;
		node* root;

		int search_remove_name(const String &name, node *& root);
		int remove_single(node* &root);

		void display_header();
		int display_subjects(const String &search, node* root);
		int display_names(const String &search, node* root);
		int display_priority(int priority, node* root);

		int load(int begin);
		void display(node* root);
		int add(node* & root,const Item &to_add);
		int copy(node* &root, node* source);
		int remove_all(node* &root);
		int size;

		void update_db();		// clear the database and then reload items from the Tree
		void update_db(node* root);	
};


// Michael Scherrer
// CS202 - programming systems
// Portland State university
// Program 3
//  -- Array, Database, node, and Tree classes -- 

#include"Tree.h"
#include<fstream>

				///////////
				// Array //
				///////////

Array::Array()
{
	size = 0;
	num_items = 0;
	items = new Item*[1];


}


Array::Array(const Array& array)
{
	size = array.size;
	num_items = array.get_num_items();
	items = new Item*[array.get_size()];
	copy(items, array.items, 0, size);
}

void Array::copy(Item** &dest, Item** source, int begin, int size)
{
	if(begin == size)
		return;

	dest[begin] = new Item(*source[begin]);

	return copy(dest, source, ++begin, size);
}

Array::~Array()
{
	remove_all(0);
	num_items = 0;
}

int Array::add(const Item &to_add)
{
	++num_items;
	return add(items, to_add, 0);
}

int Array::add(Item** &items,const Item &to_add, int begin)
{
	if(begin == size)
	{

		items[begin] = new Item(to_add);

		int double_size = (size * 2) + 1;

		Item** bigger_array = new Item*[double_size];
		expand(bigger_array, items, 0, double_size);

		remove_all(0);
		items = bigger_array;
		size = double_size;
		return 0;
	}

	if(!items[begin])
	{
		items[begin] = new Item(to_add);
		return 0;
	}

	return add(items, to_add, ++begin) + 1;
}

int Array::expand(Item** &dest, Item** source, int start, int end)
{
	if(start == end)
	{
		dest[start] = NULL;
		return 0;
	}

	if(start < num_items && source[start])
		dest[start] = new Item(*source[start]);
	else
		dest[start] = NULL;

	return expand(dest, source, ++start, end);
}

int Array::remove_all()
{
	num_items = 0;
	return remove_all(0);
}

int Array::remove_all(int begin)
{
	if(begin == size)
		return 0;

	items[begin] = NULL;

	return remove_all(++begin) + 1;
}

Item& Array::operator[](int index)
{
	return *items[index];
}

int Array::get_size() const
{
	return size;
}

int Array::get_num_items()const
{
	return num_items;
}


				//////////////
				// Database //
				//////////////


Database::Database()
{

}

Database::~Database()
{

}

void Database::show_file_list()
{
	system("ls | grep \".txt\"");
	cout << endl;
}

int Database::load(const String &file_name)
{					   
	char* file_chars = new char[100];
	file_name.substring(file_chars, 0, file_name.get_length());

	ifstream file_in; // for reading file
	char* output = new char[100];

	file_in.open(file_chars);

	if(!file_in)
	{
		cerr <<"no file found"<<endl;
		return 0;
	}

	Item* item;
	String* temp;

	do
	{
		item = new Item;
		temp = new String;

		file_in.getline(output, 100, '\n');

		temp -> set_text(output);

		if(item -> parse_item(*temp) == true)
		{
			array.add(*item);
		}

		delete item;
		delete temp;


	}while(!file_in.eof());

	file_in.close();

	return 1;
}


int Database::save(const String &file_name)
{
	String modified;

	file_name.substring(modified, file_name.get_length() - 4, file_name.get_length());

	if(modified == ".txt")
	{
		modified = file_name;
	}
	else
	{
		modified = file_name;
		modified.append(".txt");
	}

	char* file_chars = new char[0];
	modified.substring(file_chars, 0, modified.get_length());

	ofstream file_out;
	file_out.open(file_chars); // connects to a file

	if(file_out)
	{
		save(file_out, 0);
		file_out.close();
	}

	return 1;
}

int Database::save(ofstream& file_out, int begin)
{
	if(begin == array.get_num_items())
		return 0;

	file_out <<array[begin]<<endl;

	return save(file_out, ++begin) + 1;
}

void Database::display()
{
	display(0);
}

void Database::display(int begin)
{
	if(begin == array.get_size())
		return;

	array[begin].display();
	cout <<endl;

	display(++begin);
}

				//////////////
				//  node    //
				//////////////

node::node(): Item()
{
	left = 0;
	right = 0;
}

node::node(const Item &item): Item(item)
{

}

node::node(const node &source): Item(source.name, source.subject, source.url, source.priority), left(source.left), right(source.right)
{

}


node::~node()
{
	if(left)
		delete left;
	if(right)
		delete right;
}

node*& node::go_left()
{
	return left;
}

node*& node::go_right()
{
	return right;
}

void node::set_left(node* node)
{
	left = node;
}

void node::set_right(node* node)
{
	right = node;
}

				//////////////
				//  Tree    //
				//////////////

Tree::Tree()
{
	title = "priority_list";
	root = 0;

	header_top.set("Name", "Subject", "Url", 0);
	header_bottom.set("---------------------------------------------", 
			"---------------------------------------------",
			"---------------------------------------------", 0);
}

Tree::Tree(const String &name)
{
	title = name;
	root = 0;

	header_top.set("Name", "Subject", "Url", 0);
	header_bottom.set("---------------------------------------------", 
			"---------------------------------------------",
			"---------------------------------------------", 0);
}

Tree::Tree(const Tree &source)
{
	root = 0;
	copy(root, source.root);
}

int Tree::copy(node* &root, node* source)
{
	if(!source)
		return 0;

	copy(root -> go_left(), source -> go_left());
	root = new node(*source);
	copy(root -> go_right(), source -> go_right());

	return 1;
}

Tree::~Tree()
{
	remove_all();
}

int Tree::add(const Item &item)
{
	return add(root, item);
}

int Tree::add(node* &root,const Item &to_add)
{
	if(!root)
	{
		root = new node(to_add);
		root -> set_left(NULL);
		root -> set_right(NULL);

		return 0;
	}

	if(to_add >= *root)
		return add(root -> go_right(), to_add) + 1;
	else
		return add(root -> go_left(), to_add) + 1;
}

int Tree::remove(const String &name)
{
	return search_remove_name(name, root);
}

int Tree::search_remove_name(const String &name, node *& root)
{
	if(!root)
		return 0;

	if(root -> match_name(name))
	{
		return remove_single(root);
	}

	search_remove_name(name, root -> go_left());
	search_remove_name(name, root -> go_right());

	return 0;
}


int Tree::remove_single(node* &root)
{
	node * temp = new node;

	// case 2: no children
	if(!root -> go_left() && !root -> go_right())
	{
		delete root;
		root = 0;
	}
	else if(root -> go_left() && !root -> go_right()) // case 3: node has a single child on the left - delete node, replace with child
	{
		temp = root -> go_left();
		delete root;
		root = new node(*temp);
	}
	else if(!root -> go_left() && root -> go_right()) // case 3: node has a single child on the right - delete node, replace with child
	{
		temp = root -> go_right();
		delete root;
		root = new node(*temp);
	}
	else // case 4: node has a 2 or more decendants - find inorder successor
	{

		node * temp_right = root -> go_right();

		node * current = root -> go_left();

		node * temp_left = root -> go_left();

		while(current -> go_right())
		{
			current = current -> go_right();

		} // current is now the inorder successor to root

		delete root;
		root = new node(*current);

		if(temp_left != current)
			root-> go_left() = temp_left;

		root -> go_right() = temp_right;

		remove_single(current); // remove the inorder successor
	}

	return 1;
}

int Tree::remove_all()
{
	return remove_all(root);
}

int Tree::remove_all(node* &root)
{
	if(!root)
		return 0;

	remove_all(root -> go_left());
	remove_all(root -> go_right());

	delete root;
	root = NULL;

	return 1;
}

int Tree::load(const String &file_name)
{
	Database::load(file_name);
	title = file_name;
	load(0);
	return 1;
}

int Tree::load(int begin)
{
	if(begin == array.get_num_items())
		return 0;

	add(array[begin]);

	return load(++begin) + 1;
}

int Tree::save()
{ 
	update_db();
	Database::save(title);
	return 1;
}

void Tree::update_db()
{
	array.remove_all();
	update_db(root);
}

void Tree::update_db(node* root)
{
	if(!root)
		return;


	update_db(root -> go_left());

	array.add(*root);

	update_db(root -> go_right());

	return;
}

void Tree::display_header()
{
	cout<<"		"<< title <<endl;
	cout<<endl;
	header_top.display(10);
	header_bottom.display(10);
}

void Tree::display()
{
	display_header();
	display(root);
}

void Tree::set_title(const String& title)
{
	this -> title = title;
}

void Tree::display(node* root)
{
	if(!root)
		return;

	display(root -> go_right());
	root -> display(10);
	display(root -> go_left());

	return;
}

int Tree::display_subjects(const String &search)
{
	display_header();
	return display_subjects(search, root);
}

int Tree::display_subjects(const String &search, node* root)
{

	if(!root)
		return 0;

	display_subjects(search, root -> go_right());

	if(root -> contains_subject(search))
		root -> display(10);

	display_subjects(search, root -> go_left());

	return 0;

}

int Tree::display_names(const String &search)
{
	display_header();
	return display_names(search, root);
}

int Tree::display_names(const String &search, node* root)
{

	if(!root)
		return 0;

	display_names(search, root -> go_right());

	if(root -> contains_name(search))
		root -> display(10);

	display_names(search, root -> go_left());

	return 0;

}

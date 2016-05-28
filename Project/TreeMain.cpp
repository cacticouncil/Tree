// TreeMain.cpp - the entry point of the tree application
// Code by Cromwell D. Enage, December 2008
// Updated by Jeremiah Blanchard, January 2009
// Updated by Cromwell D. Enage, April 2009
#include <limits>
#include <string>
#include <iostream>
#include "Tree.h"

using namespace std;

// Wrappers.
class SizeHolder { SizeHolder(); friend SizeHolder create(size_t element); public: size_t held; };
struct StringHolder { string beans; };
SizeHolder create(size_t element);


// Prototypes (so that implementations may go after main)
bool isNotLeafSize(SizeHolder const& element);
void createSizeNodes(TreeNode<SizeHolder>* node);
void printSize(SizeHolder& element);

bool isNotLeafString(char* const& data);
void createStringNodes(TreeNode<char*>* node);
void printString(char*& data);
void pruneString(char*& data);
void deleteString(char*& data);
void assert_pause(bool condition, string message);

template <typename T, typename Predicate, typename Function>
void buildTree(TreeNode<T>* node, Predicate& canHaveChildElements, Function& createChildren);

int main()
{
	// Everything must compile.
	TreeNode<StringHolder> dummy;

	// Run the tests.
	TreeNode<SizeHolder>* size_root = new TreeNode<SizeHolder>(create(5));
	TreeNode<char*>* string_root = new TreeNode<char*>();
	assert_pause(string_root->getData() == nullptr, "You did not default-construct your data member: [string_root->getData() == nullptr].");

	buildTree(size_root, isNotLeafSize, createSizeNodes);
	cout << "After construction," << endl << "    Breadth-first traversal:";
	breadthFirstTraverse(size_root, printSize);
	cout << endl << "    Pre-order traversal:";
	preOrderTraverse(size_root, printSize);
	cout << endl << "    Post-order traversal:";
	postOrderTraverse(size_root, printSize);
	cout << endl << endl;

	size_root->getChild(4)->deleteChildren();
	cout << "After deleteChildren call," << endl << "    Breadth-first traversal:";
	breadthFirstTraverse(size_root, printSize);
	cout << endl << "    Pre-order traversal:";
	preOrderTraverse(size_root, printSize);
	cout << endl << "    Post-order traversal:";
	postOrderTraverse(size_root, printSize);
	cout << endl << endl;

	char* root_data = new char[2];
	root_data[0] = '5';
	root_data[1] = '\0';
	string_root->getData() = root_data;

	buildTree(string_root, isNotLeafString, createStringNodes);
	cout << "After construction," << endl << "    Breadth-first traversal:";
	breadthFirstTraverse(string_root, printString);
	cout << endl << "    Pre-order traversal:";
	preOrderTraverse(string_root, printString);
	cout << endl << "    Post-order traversal:";
	postOrderTraverse(string_root, printString);
	cout << endl << endl;

	TreeNode<char*>* prune_string = string_root->getChild(4);
	postOrderTraverse(prune_string, pruneString);
	prune_string->deleteChildren();
	cout << "After deleteChildren call," << endl << "    Breadth-first traversal:";
	breadthFirstTraverse(string_root, printString);
	cout << endl << "    Pre-order traversal:";
	preOrderTraverse(string_root, printString);
	cout << endl << "    Post-order traversal:";
	postOrderTraverse(string_root, printString);
	cout << endl << endl;

	postOrderTraverse(string_root, deleteString);
	delete string_root;
	delete size_root;

	cout << "Press ENTER to continue..." << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	return 0;
}

SizeHolder::SizeHolder()
{
}

SizeHolder create(size_t element)
{
	SizeHolder holder;
	holder.held = element;
	return holder;
}

void printSize(SizeHolder& element)
{
	cout << ' ' << element.held;
}

bool isNotLeafSize(SizeHolder const& element)
{
	return 1 < element.held;
}

void createSizeNodes(TreeNode<SizeHolder>* node)
{
	TreeNode<SizeHolder>* child;

	for (size_t i = 0; i < node->getData().held; ++i)
	{
		child = new TreeNode<SizeHolder>(create(i));
		node->addChild(child);
		assert_pause((child == node->getChild(i)), "You\'re not linking the parent to its child: [child == node->getChild(i)].");
	}
}

bool isNotLeafString(char* const& data)
{
	return '1' < data[0];
}

void createStringNodes(TreeNode<char*>* node)
{
	TreeNode<char*>* child = 0;
	char* data = 0;

	// I'd use Ewok names instead if I actually remembered any of them...
	for (char charbinx = '0'; charbinx < node->getData()[0]; ++charbinx)
	{
		child = new TreeNode<char*>();
		node->addChild(child);

		char*& data = child->getData();

		assert_pause(data == nullptr, "You did not default-construct your data member: [data == nullptr].");
		data = new char[2];
		data[0] = charbinx;
		data[1] = '\0';
		assert_pause((child == node->getChild(charbinx - '0')), "You\'re not linking the parent to its child: [child == node->getChild(charbinx - '0')].");
	}
}

void printString(char*& data)
{
	cout << ' ' << data;
}

void pruneString(char*& data)
{
	if (data[0] < '4')
	{
		delete[] data;
	}
}

void deleteString(char*& data)
{
	delete[] data;
}


template <typename T, typename Predicate, typename Function>
void buildTree(TreeNode<T>* node, Predicate& canHaveChildElements, Function& createChildren)
{
	std::list<TreeNode<T>*> nodeQueue;
	nodeQueue.push_back(node);

	while (!nodeQueue.empty())
	{
		node = nodeQueue.front();
		nodeQueue.pop_front();

		if (canHaveChildElements(node->getData()))
		{
			createChildren(node);
		}

		for (auto child : node->getChildren())
		{
			nodeQueue.push_back(child);
		}
	}
}

void assert_pause(bool condition, string message)
{
	if (!condition)
	{
		cout << message << endl;
		cout << "Press ENTER to abort..." << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		abort();
	}
}
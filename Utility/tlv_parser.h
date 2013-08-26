// This class represents a tree-like structure of TLV objects.
// The tree is created by recuirsivly parsing a binary array containing concatinated
// list of TLV-coded values. TLV could be nested in cases when TLV has a constucted type.
// The tree can be traversed by using the functions provided by the class.
//This class is part of Utility library of SmartPOS project.

#ifndef TLV_PARSER_H
#define TLV_PARSER_H

#include "tlv.h"
#include <list>

using namespace std;

class tlv_parser;

typedef list<tlv_parser*> TLV_LIST;

class tlv_parser
{
public:
	tlv_parser(void);
	virtual ~tlv_parser(void);
	
	// Parses a buffer and creates a tree-like structure of TLV values.
	// It is a recursive function.
	// It parses an array header into the tree of the TLV data objects.
	// The tree consists of the nodes where each node is tlv_parse type.
	// tlv_parse object has a pointer to the tlv object and a list of all
	// child nodes directly under the root node. Each child node is represented by 
	// tlv_parse object in the list.
	// Returns SUCCESS if succeeds or error code otherwise
	int parse(byte *header, int len); 

	// Returns a root of the tree, which is a tlv object
	tlv *GetRoot();

	// Returns the first child of the node, which is a tlv_parser object (NULL if 
	// there are no children)
	tlv_parser *GetFirstChild();
	// Returns a next child of the node, which is a tlv_parser object (NULL if there are
	// no more children in this node)
	tlv_parser *GetNext();

	int GetPaddedBytesQty();

	// Returns the number of the children in for this node
	int Count();

	// Resets the tree -- removes all nodes
	void reset();

	// Finds a node in a tree which root has a tag specified as a first argument
	tlv_parser *Find (int Tag, bool IncludeSubTrees = false);
	// Finds a first node in a tree which root has a tag specified as a first argument
	tlv_parser *FindFirst(int Tag);
	// Finds a next node with the same tag as was used by previuos call to the FindFirst function
	tlv_parser *FindNext();

	byte *GetTlvDataObject(); // Returns a pointer to the Data Object (including tag, length, value)
	byte *CopyTlvDataObject(); // Allocates a new buffer and copies this Data Object into it (a buffer needs to be deallocated by a caller)
	int GetTlvDataObjectLen(); // Returns the total length of the Data Object including length of the tag, length, and value

	int GetLeadingPad();
	int GetMidPad();
	int GetTrailingPad();

private:
	
private:
	TLV_LIST lstChildren;
	tlv *tlvRoot;
	list<tlv_parser*>::iterator it;
	tlv_parser *tlv_anchor;
	int searchTag;
	int PaddedBytes;
	int Offset;
	int Reminder;
};

#endif


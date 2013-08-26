#include "tlv_parser.h"

tlv_parser::tlv_parser(void)
{
	it = NULL;
	tlvRoot = NULL;
	searchTag = 0;
	tlv_anchor = NULL;
	Offset = 0;
	Reminder = 0;
}

tlv_parser::~tlv_parser(void)
{
	reset();
}

void tlv_parser::reset()
{
	if (tlvRoot)
	{
		delete tlvRoot;
		tlvRoot = NULL;
	}
	while (lstChildren.size() > 0)
	{
		tlv_parser *pTemp = lstChildren.front ();
		delete pTemp;
		lstChildren.pop_front ();
	}
	it = NULL;
	// Initialize a counter of padded bytes
	PaddedBytes = 0;
	Offset = 0;
	Reminder = 0;
}

tlv *tlv_parser::GetRoot()
{
	return tlvRoot;
}

// It is a recursive function.
// It parses an array header into the tree of the TLV data objects.
// The tree consists of the nodes where each node is tlv_parse type.
// tlv_parse object has a pointer to the tlv object and a list of all
// child nodes directly under the root node. Each child node is represented by 
// tlv_parse object in the list.
int tlv_parser::parse(byte *header, int len)
{
	// Check if the root exists, and if it is, then reset the object
	if (tlvRoot)
		reset();

	if (len <= 0)
		return TLV_INVALID_LENGTH_VALUE;

	// Initialize counter keeping the number of padded bytes to 0
	Offset = tlv::findDataStartPoint (header, len);
	if (Offset >= len)
		return TLV_NO_DATA;

	// Create a root object which is a tlv coded data object
	tlvRoot = new tlv();
	if (!tlvRoot)
		return ERR_MEMORY_ALLOC;

	// Parse the array into tlv object
	int res = tlvRoot->SetTlv (header + Offset, len);
	if (res != SUCCESS)
	{
		// header array has invalid data not recognized as TLV encoding
		delete tlvRoot;
		tlvRoot = NULL;
		return res;
	}
	
	int curIndx;
		
	// If the parsed value is primitive TLV type, then do not do anything else.
	// If the type is constructed (not primitive), then do additional parsing
	// for each embedded tlv object.
	if (!tlvRoot->IsPrimitive())
	{
		// Go through the contents of the value and initialize all
		//   embedded TLV's
		int val_length = tlvRoot->GetLengthVal ();
		curIndx = 0;
		while (curIndx < val_length)
		{
			// Create a new tlv_parser object which will keep the embedded TLV object
			tlv_parser *tlv_child = new tlv_parser();
			if (!tlv_child)
			{
				//reset();
				return ERR_MEMORY_ALLOC;
			}
			
			// Parse the embedded TLV object
			res = tlv_child->parse (tlvRoot->GetValue () + curIndx,
									val_length - curIndx);
			if (res != SUCCESS)
			{
				// Error parsing a TLV object
				delete tlv_child;
				reset();
				return res;
			}

			// Push a newely created TLV object into the list of children roots 
			lstChildren.push_back (tlv_child);

			// Update the current index to move to the next embedded TLV object
			curIndx += tlv_child->GetTlvDataObjectLen();
		}
	}
	
	// Calculate a Reminder for premitive Data Object
	if (Offset + tlvRoot->GetDataObjectLen() < len)
	{
		Reminder = tlv::findDataStartPoint (header + Offset +
			tlvRoot->GetDataObjectLen (), 
			len - Offset - tlvRoot->GetDataObjectLen ());
	}
	
	return SUCCESS;
}


tlv_parser* tlv_parser::GetFirstChild()
{
	it = lstChildren.begin();
	if (it != lstChildren.end())
		return *it;
	else
		return NULL;
}

tlv_parser* tlv_parser::GetNext()
{
	if (it != NULL)
	{
		it++;
		if (it != lstChildren.end())
			return *it;
		else
			return NULL;
	}
	else 
		return NULL;
}

int tlv_parser::Count()
{
	return (int)lstChildren.size ();
}

// Finds and returns a tlv_parser object which root element has a tag specified
// in the first argument.
// If IncludeSubTrees is FALSE (default), only the root and the children directly
// below the root are checked.
// If IncludeSubTrees is TRUE, then the entire tree is searched.
// If the tag is not found, the function returns NULL.
tlv_parser* tlv_parser::Find (int Tag, bool IncludeSubTrees)
{
	if (!tlvRoot)
		return NULL;

	if (tlvRoot->GetTagVal () == Tag)
		return this; // The root element has a tag specified


	// Do preorder traversal of the tree
	tlv_parser *parser_child = GetFirstChild();
	while (parser_child)
	{
		if (!IncludeSubTrees)
		{   // Do this branch if only children at the first level are checked
			if (parser_child->GetRoot ()->GetTagVal () == Tag)
				return parser_child;
		}
		else
		{ // check all the subtrees
			parser_child = parser_child->Find(Tag, IncludeSubTrees);
			if (parser_child)
				return parser_child;
		}
		parser_child = GetNext (); // Go to the next child
	}
	return NULL; // A Tag is not found in this tree
}


tlv_parser* tlv_parser::FindFirst(int Tag)
{
	tlv_anchor = NULL;
	if (!tlvRoot)
		return NULL;

	if (tlvRoot->GetTagVal () == Tag)
		return this; // The root element has a tag specified

	searchTag = Tag;
	tlv_parser *tlv_child = GetFirstChild();
	while (tlv_child)
	{
		// Do this branch if only children at the first level are checked
		if (tlv_child->GetRoot ()->GetTagVal () == Tag)
		{
			tlv_anchor = this;
			return tlv_child;
		}
		tlv_child = GetNext ();
	}

	tlv_anchor = NULL;
	searchTag = 0;
	return NULL; // A Tag is not found in this tree
}

tlv_parser* tlv_parser::FindNext()
{
	if (!tlv_anchor)
		return NULL;
	tlv_parser *tlv_child = tlv_anchor->GetNext ();
	while (tlv_child)
	{
		// Do this branch if only children at the first level are checked
		if (tlv_child->GetRoot ()->GetTagVal () == searchTag)
			return tlv_child;
		tlv_child = tlv_anchor->GetNext ();
	}
	tlv_anchor = NULL;
	searchTag = 0;
	return NULL;
}

int tlv_parser::GetPaddedBytesQty()
{
	return PaddedBytes;
}

// Returns a pointer to the Data Object (including tag, length, value)
byte *tlv_parser::GetTlvDataObject()
{
	if (tlvRoot)
		return tlvRoot->GetDataObject () - Offset;
	else
		return 0;
}

// Allocates a new buffer and copies this Data Object into it 
// (a buffer needs to be deallocated by a caller)
byte *tlv_parser::CopyTlvDataObject()
{
	if (tlvRoot)
	{
		byte *tt = new byte [GetTlvDataObjectLen()];
		if (!tt)
			return 0;
		else
		{
			memcpy (tt, GetTlvDataObject(), GetTlvDataObjectLen());
			return tt;
		}
	}
	else
		return 0;

}

// Returns the total length of the Data Object including length of the tag, 
// length, value, and padded bytes
int tlv_parser::GetTlvDataObjectLen()
{
	if (tlvRoot)
		return Offset + GetRoot()->GetDataObjectLen () + Reminder;
	else
		return 0;
}

int tlv_parser::GetLeadingPad()
{
	return Offset;
}

int tlv_parser::GetMidPad()
{
	return PaddedBytes;
}

int tlv_parser::GetTrailingPad()
{
	return Reminder;
}


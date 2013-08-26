/*==========================================================================
 *
 *  !PROPERTIES.H   functions								   June 10, 2005
 *
 *  Definitions for Properties File Utililty Functions
 * 
 *  Utility functions to read properties from a properties file and load them
 *  into memory as a linked list. Once read, any property can be accessed at
 *  any point of time by calling the getProperty function.
 *
 *  Author: Manav Garg (manav_garg@hotmail.com)
 *==========================================================================*/

#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_


/* ------------------------------------------------------------------------ */
/* ---------------------------  HEADER FILES    --------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ------------------------------------------------------------------------ */
/* ---------------------------  SIZE CONSTANTS   -------------------------- */
#define MAXDATASIZE   1024
#define MAXPROPSIZE   256
#define MAXVALUESIZE  2048
#define DELIMITER     "="
#define DELIMITERSIZE 1
#define TRUE          1
#define FALSE         0
#define ISDEBUG       FALSE 

/* ------------------------------------------------------------------------ */
/* -------------------------  STRUCTURE DEFINITIONS ----------------------- */
typedef struct list {
    char *property;
    char *value;
    struct list *next;
} PROPERTY;

//Type definition for the node of the properties list
PROPERTY *node= NULL;  

//File pointer
FILE *fp = NULL;

/*----------------------------------------------------------------------------
 * Loads the properties file
 * IN >> filename (Name of the properties file)
 * OUT<< None
 */
int loadPropertyFile( char *filename );

/*----------------------------------------------------------------------------
 * Loads the properties from the properties file
 * IN >> None
 * OUT<< None
 */
void loadProperties();

/*----------------------------------------------------------------------------
 * Displays the properties read from the properties file (debug function)
 * IN >> None
 * OUT<< None
 */
void listProperties (void);

/*----------------------------------------------------------------------------
 * Cleans up the data structures created to read the properties
 * [DO NOT FORGET TO CLEANUP AT THE END OF THE APPLICATION TO AVOID
 *  EATING UP YOUR MEMORY]
 * IN >> None
 * OUT<< None
 */
void cleanup (void);    

/*----------------------------------------------------------------------------
 * Add the property read from the file to the internal data structure
 * IN >> property  (Property name) 
 * IN >> value     (Corresponding value of the property)
 * OUT<< None
 */
void addProperty (char *property, char *value);

/*----------------------------------------------------------------------------
 * Get the value of a property (from the list) 
 * IN >> property  (Property name) 
 * OUT>> value     (Returns value of the corresponding property)
 */
void getProperty (const char *property, char *value);

/*----------------------------------------------------------------------------
 * Returns the count of properties currently loaded in the list
 * IN >> None
 * OUT<< int count (The count of properties currently present in memory)
 */
int getPropertyCount();

/*----------------------------------------------------------------------------
 * Cleans up the data structures created to read the properties
 * IN >> search    (The string that is to be searched)
 * IN >> string    (The source string)
 * IN >> offset    (Offset on where to begin the search in 'string')
 * OUT<< int index (Index on where 'search' was found in 'string')
 */
int searchString (const char *search, const char *string, int offset);

/*----------------------------------------------------------------------------
 * Get the value of a property (from the list) 
 * IN >> s		   (String to be trimmed) 
 * OUT>> char *    (Trimmed input string)
 */
static char *trim( char *s);

#endif /* !_PROPERTIES_H_ */

/*==========================================================================*/

/// Luke Mitchell lm0466
// Principles of programming CW2
// Hash table/Linked list assignment

// Main program body
// Reads a text file, populates a hash table and a linked list from the contents
// and returns the number of occurences for specified words.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "list.h"
#include "hash.h"

// Converts a string to UPPERCASE
// Returns the new, uppercase string
char* capitalise_string (char* str)
{
	int i = 0;
		
	while (str[i] != '\0')
	{
		str[i] = toupper (str[i]);
		i++;
	}

	return str;
}

// Checks if character c is punctuation
// Returns 0 if not, or 1 if so.
int is_punctuation (char c)
{
	// array of punctuation characters
	const char punctuation[] = { '.', ',', '-', '`', '\'', '\"', '?', '!', ';', ':', '&', '%' };
	
	// iterator
	int i;

	for (i = 0; i < sizeof(punctuation); i++)
		if (punctuation[i] == c)
			return 1;

	return 0;
}

// Checks if character c is whitespace
// Returns 0 if not, or 1 if so
int is_whitespace (char c)
{
	// array of whitepsace characters
	const char whitespace[] = { ' ', '\t', '\n' };
	
	// iterator
        int i;

        for (i = 0; i < sizeof(whitespace); i++)
                if (whitespace[i] == c)
                        return 1;

        return 0;
}

// Adds a letter, c, to a string, str
char* add_letter_to_string (char* str, char c)
{
	int len = 0;
	char *buf = NULL;

	// empty string?
	if (str)
	{
		// no, it's not
		// copy str->buf
		len = strlen (str);
		buf = calloc (len, sizeof (char));
		strncpy (buf, str, len);

		// resize buf
		free (str);
		str = calloc (len + 1, sizeof (char));
					
		// copy buf->str
		strncpy (str, buf, len);

		// and add the letter
		strncpy (&str[len], &c, 1);

		// free buf
		free (buf);
	}
	else
	{
		// yes
		// allocate a buffer	
		len = 1;
		str = calloc (len, sizeof (char));
					
		// and add the letter
		strncpy (str, &c, len);
	}

	return str;

}

// Opens the specified file, filename, and reads each word in turn.
// Words are then added to the linked-list and the hash table.
// returns -1 for 'file doesn't exist'
// returns 0 on success
int read_data (list* l, hashtable* h, char* filename)
{
	// file pointer and flags/vars
	FILE *fp;
	int i, end_of_file = 0, words_read = 0;
	
	// timer variables
	struct timeval start, end;
	long elapsed_usec;
	double elapsed_sec;
	
	// buffer variables for reading in words
	char w;
	char *buf = NULL;

	// open the file for reading
	if ((fp = fopen (filename, "r")))
	{
		for (i = 0; i < 2; i++)
		{
			// 'start' the timer
			gettimeofday (&start, NULL);

			// read each word into the list and hashtable
			while (!end_of_file)
			{		
				while (1)
				{
					// get character
					w = fgetc (fp);

					// check for whitespace
					// to indicate a new word
					if (is_whitespace(w))
						break;

					// check for punctuation
					// ignore it if so
					if (is_punctuation(w))
						continue;

					if (w == EOF)
					{
						end_of_file = 1;
						break;
					}

					//add letter to the buffer
					buf = add_letter_to_string (buf, w);
				}

				if (buf)
				{
					// add null byte
					buf = add_letter_to_string (buf, '\0');
				
					// capitalise letter, to avoid case discrepencies	
					// i.e. at the start of sentences
					char* capitalised = capitalise_string (buf);

					// add to current ADS
					node* n;

					if (i == 0)
					{
						// add to/update list
						n = list_search (l, capitalised);

						if (n)
							n->count++;
						else	
				        		list_add_node (l, capitalised, 1);
					}
					else
					{
				       		// add to/update hashtable
						n = hashtable_search (h, capitalised);
				
						if (n)
							n->count++;
						else
							hashtable_add_node (h, capitalised, 1);
					}

					// increment words read counter
					words_read++;
				}				

				// free memory from buffer
				free (buf);
				buf = NULL;
			}

			// 'stop' the timer
			gettimeofday (&end, NULL);

			// work out the difference
			elapsed_usec = (end.tv_sec - start.tv_sec) * 100000; // convert to usec
			elapsed_usec += (end.tv_usec - start.tv_usec);
			elapsed_sec = (elapsed_usec / 1000000.0f);

			// print time/word count information
			printf ("Reading into a %s took %.2fs for %d words\r\n", ((i == 0) ? "list" : "table"), elapsed_sec, words_read);

			// reset word counter
			words_read = 0;

			// reset end_of_file flag
			end_of_file = 0;
	
			// seek back to file start
			rewind (fp);
		}

		// close it
		fclose (fp);
	}
	else
	{
		// file doesn't exist
		return -1;
	}

	// return success
	return 0;
}

// Handle a query for a particular word, w.
// Prints the number of occurences for the word, along with
// the number of comparisons the operation takes in both the list, l,
// and the hash table, h.
void handle_query (list* l, hashtable* h, char* w)
{
	int list_cmp = 0, table_cmp = 0, occurrences = 0;
	node* n;

	// capitalise the word, as this is how values are stored in the data structures
	char* capitalised = capitalise_string (w);

	list_cmp = list_get_comparisons (l, capitalised);
	table_cmp = hashtable_get_comparisons (h, capitalised);

	// get number of occurrences
	// using the hashtable as this will be significantly faster
	n = hashtable_search (h, capitalised);

	if (n)
	{
		occurrences = n->count;
	}

	// print data	
	printf ("\'%s\' occurs %d times\r\n", w, occurrences);
	printf ("Retrieval from list took %d comparisons.\r\n", list_cmp);
	printf ("Retrieval from table took %d comparisons.\r\n", table_cmp);
}

// Main program body
// Creates data structures, populates them and prompts the user for queries
int main (int argc, char** argv)
{
	// variables for handling queries
	// this assumes a maximum word length of 32
	char yn, w[32];

	// create the data structures
	list* l = list_create ();
	hashtable* h = hashtable_create ();
		
	// allocated?
	if (!l || !h)
	{	
		printf ("Could not allocate enough memory\r\n");
		return -1;	
	}

	// was a text file specified? if not print usage information
	if (argc < 2)
	{
		printf ("Usage: %s christmas_carol.txt\r\n", argv[0]);
		return -1;
	}

	// read all of the words from the text file into a hash table and a linked list
	if ((read_data (l, h, argv[1]) != 0))
	{
		printf ("The filename specified, %s, does not exist\r\n", argv[1]);
		return -1;
	}

	// get some statistics about the hashtable	
	int i, highest = 0;
	float empty = 0;
	
	for (i = 0; i < h->size; i++)
	{
		if (h->table[i])
		{
			// check for highest number of collisions
			// first checking that h->table[highest] exists to avoid segfault
			if (h->table[highest])
			{
				if (h->table[i]->size > h->table[highest]->size)
					highest = i;
			}
			else
			{
				highest = i;
			}
		}
		else
		{
			empty++;
		}
	}

	// and print them, in a neat fashion
	printf ("\r\n");
	printf ("Hash table statistics:\r\n");
	printf ("\tsize of the hashtable is %d\r\n", h->size);
	printf ("\tnumber of empty table indexes is %.0f\r\n", empty);
	printf ("\tpercentage of hashtable used is %.2f%%\r\n", (1 - (empty / h->size)) * 100);
        printf ("\tmaximum length of overflow list is %d\r\n", h->table[highest]->size);	
	printf ("\r\n");

	// get the queries for word occurences
	// 'Another query? [Y/n]' defaults to y
	while (1)
	{
                printf ("Enter word for retrieval: ");

		if (scanf ("%s", w))
                	handle_query    (l, h, w);

                printf ("\r\n");
                
		// next query?
		printf ("Another query? [Y/n] ");

		// flush buffer...
		while ((yn = getchar()), yn != '\n' && yn != EOF)
			;
	
		yn = getchar ();
		printf ("\r\n");
		
		if (yn == 'n' || yn == 'N')
			break;
		
		if (yn == 'n' || yn == 'N')
			break;
        }

	// exit successfully
	return 0;
}		



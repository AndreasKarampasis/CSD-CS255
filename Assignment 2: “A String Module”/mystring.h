/*Andreas Karampasis csd3777
*askisi2 mystring.h
*/
#ifndef STRING_H_
#define STRING_H_
#include <stddef.h>
/*Return the length of the string
 *assert if string is NULL
 */
size_t ms_length(const char *pcStr);

/*Copy str from src into dest
 *assert if src string is NULL
 */
char *ms_copy(char *dest, const char *src);

/*Copy n chars from src into dest
 *WARNING! if no null byte in first n bytes
 *str will not be null-terminated
 */
char *ms_ncopy(char *dest, const char *src, size_t n);

/*Append the src string to the dest str
 *Overwrites the null byte of the dest and then
 *adds a terminating null byte(\0).
 */
char *ms_concat(char *dest, const char *src);

/*Similar to ms_concat but it will use at most n bytes
 *from src and src doesnt need to be null terminated
 *if it contains n or more bytes
 */
char *ms_nconcat(char *dest, const char *src, size_t n);

/*Compares the two strings s1 and s2. If s1 matches with s2
 *return 0 , if s1 is less than s2 return an int less than 0
 *if s1 is greater than s2 then return an int greater than 0
 */
int ms_compare(const char *s1, const char *s2);

/*Similar to ms_compare but it compares only the 
 *first(up to) n bytes of s1 and s2
 */
int ms_ncompare(const char *s1, const char *s2, size_t n);

/*Searches the substring needle  in the string haystack.
 *The terminating null bytes(\0) are not compared
 */
char *ms_search(char *haystack, char *needle);

#endif

/*Andreas Karampasis csd3777
 *askisi2 mystring_ptrs.c*/
#include "mystring.h"
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
/*Return the length of the string
 *assert if string is NULL
 */
size_t ms_length(const char *s){
  const char *sEnd = s;
  assert(s != NULL);
  while(sEnd != '\0'){
    sEnd++;
  }
return (sEnd-s);
}

/*Copy str from src into dest
 *assert if src string is NULL
 */
char *ms_copy(char *dest, const char *src){
  char *newDest = dest;
  assert(src != NULL);
  while(*src){
	*newDest++ = *src++;
  }
/*Ensure trailing null byte is copied*/
  *newDest = '\0';
  return dest;
}

/*Copy n chars from src into dest
 *WARNING! If no null byte in first n bytes
 *the string placed in dest will not be null terminated
 *assert if src is NULL
 */
char *ms_ncopy(char *dest, const char *src, size_t n){
  char *newDest = dest;
  assert(src != NULL);
  while(*src && n){
	*newDest++ = *src++;
	 n--;
	
  }
/*Ensure trailing null byte is copied*/
 if(n > 0) *newDest = '\0';
return dest;
}

/*Append the src string to the dest string
 *Overtwrites the null byte of the dest and then
 *adds a terminating null byte
 */
char *ms_concat(char *dest, const char *src){
   size_t dest_len = ms_length(dest);
   size_t i;
   assert(src != NULL);
   for(i = 0; src[i] != '\0'; i++){
	dest[dest_len + i] = src[i];
   }
/*Ensure trailing null byte is copied*/
	dest[dest_len + i] = '\0';
return dest;
}

/*Similar to ms_concat but it will use at most n bytes
 *from src and src doesnt need to be null terminated
 *if it contains n or more bytes
 */
char *ms_nconcat(char *dest, const char *src, size_t n){
    size_t dest_len = ms_length(src);
    size_t i;
    assert(src != NULL);
    for(i = 0; i < n && src[i] != '\0'; i++){
	dest[dest_len + i] = src[i];
   }
/*Ensure trailing null byte is copied*/
	dest[dest_len + i] = '\0';
return dest;
}

/*Comapres the two strings s1 and s2, if s1 matches with s2
 *return 0, if s1 is less than s2 return an int less than 0
 *if s1 is greater than s2 then return an int greater than 0
 */
int ms_compare(const char *s1, const char *s2){
   assert(s1 != NULL);
   assert(s2 != NULL);
   while(*s1 || *s2){
      if(*s1 != *s2){
	return (*s1 > *s2 ? 1 : -1);
      }
	s1++;
	s2++;
   }
	return 0;
  }

/*Similar to ms_compare but it compares only the 
 *first (up to) n bytes of s1 and s2
 */
int ms_ncompare(const char *s1, const char *s2, size_t n){
   assert(s1 != NULL);
   assert(s2 != NULL);
   while(n){
      if(*s1 != *s2){
	 return(*s1 > *s2 ? 1 : -1);
      }
      s1++;
      s2++;
      n--;
   }
   return 0; 
}

/*Searches the substring "needle" in the string "haystack".
 *The terminating null bytes are not compared
 */
char *ms_search(char *haystack, char *needle){
/*The size of needle without the '\0*/
   size_t i = ms_length(needle) - 1;
   assert(haystack != NULL);
   assert(needle != NULL);
   while(*haystack){
      if(*haystack == *needle){
	if(*(needle + 1) == '\0'){
		return (haystack - i);
	}
	needle++;
      }
     else haystack++;
   }
return NULL;
}

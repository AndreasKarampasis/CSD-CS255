
#include "mystring.h"
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
/*Return the length of the string
 *assert if string is NULL
 */
size_t ms_length(const char s[]){
  size_t length = 0;
  assert(s != NULL);
  while(s[length] != '\0'){
	length++;
  }
return length;
}
/*Copy str from src into dest
 *assert if src string is NULL
 */
char *ms_copy(char dest[], const char src[]){
  size_t i;
  assert(src != NULL);
  for(i = 0; src[i] != '\0'; i++){
	dest[i] = src[i];
  }
/*Ensure trailing null byte is copied*/
	dest[i] = '\0';
  return dest;
}

/*Copy n chars from src into dest
 *WARNING! If no null byte in first n bytes
 *the string placed in dest  will not be null terminated
 *assert if src is NULL
 */
char *ms_ncopy(char dest[], const char src[], size_t n){
  size_t i;
  assert(src != NULL);
  for(i = 0; i < n && src[i] != '\0'; i++){
	dest[i] = src[i];
  }
/*Ensure trailing null byte is copied*/
	dest[i] = '\0';
  return dest;
}

/*Append the src string to the dest str
 *Overwrites the null byte of the dest and then
 *adds a terminating null byte
 */
char *ms_concat(char dest[], const char src[]){
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
char *ms_nconcat(char dest[], const char src[], size_t n){
   size_t dest_len = ms_length(dest);
   size_t i;
   assert(src != NULL);
   for(i = 0; i < n && src[i] != '\0'; i++){
	dest[dest_len + i] = src[i];
   }
/*Ensure trailing null byte is copied*/
	dest[dest_len + i] = '\0';
   return dest;
}

/*Compares the two strings s1 and s2, if s1 mathces with s2
 *return 0, if s1 is less than s2 return an int less than 0
 *if s1 is greater than s2 then return an int greater than 0
 */
int ms_compare(const char s1[], const char s2[]){
 size_t i;
 assert(s1 != NULL);
 assert(s2 != NULL);
  for(i = 0; ; i++){
	if(s1[i] != s2[i]){
/*if s1[i] > s2[i] return 1 else return -1*/
	   return (s1[i] > s2[i] ? 1 : -1);
	}
/*This means s1 == s2*/
	if(s1[i] == '\0'){
	   return 0;
	}
  }
}

/*Similar to ms_compare but it compares only the
 *first(up to) n bytes of s1 and s2
 */
int ms_ncompare(const char s1[], const char s2[], size_t n){
  size_t i = 0;
  assert(s1 != NULL);
  assert(s2 != NULL);
  while(n){
     if(s2[i] != s1[i]){
	return (s1[i] > s2[i] ? 1 : -1);
     }
     i++;
     n--;
  }
	return 0;
  
}

/*Searches the substring "needle" in the string "haystack".
 *The terminatng null bytes are not compared
 */
char *ms_search(char haystack[], char needle[]){
  size_t i = 0;
  size_t j = 0;
  assert(haystack != NULL);
  assert(needle != NULL);

  for(i = 0; haystack[i] != '\0'; i++){
     if(haystack[i] == needle[j]){
	if(needle[j + 1] == '\0'){
	   return haystack + (i - j);
	}
	j++;
     }
     else  j = 0;
  }
return NULL;
}

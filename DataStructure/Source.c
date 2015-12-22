#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int countFrequency(const char* str, char ch);
char* filterString(const char* input);
char* filterString2(char* input);

/*int main(){
	char str[1000];
	gets(str);
	
	char ch;
	scanf("%c", &ch);

	int nullValue = '\0';
	printf("%d\n", nullValue);

	return EXIT_SUCCESS;			
}*/

//frequency of character
int countFrequency(const char* str,const char ch){
	int count = 0;
	int thisChar = 0;
	while (thisChar = *str++){
		if (ch == thisChar)
			 count+=1;

	}
	printf("Last Value of thisChar %d", thisChar);// should be the int equivalent of null
	return count;
}

//remove all characters except chars - return a new string
char* filterString(const char* input){
	int length = strlen(input);
	char* newStr = malloc(sizeof(char)* (length + 1));
	int i = 0; //loop over ibput
	int j = 0;//loop over output
	int ch = 0;
	for (i = 0, j = 0; i < length;){ //better to use while
		//ch = input[i];
		ch = *input++;

		if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))){
			++i;
		}
		else{
			//newStr[j++] = input[i++];
			newStr[j++] = (char)ch;
		}
	}
	newStr[j] = '\0';
	return newStr;
}


//remove all characters except chars in the same string
char* filterString2(char* input){
	int length = strlen(input);
	int i = 0; //loop over input
	int j = 0; //new String index
	int ch = 0;
	while (ch = input[i]){

		if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))){
			i++; //do nothing
		}
		else{
			input[j++] = input[i++];
		}
	}
	input[j] = '\0';
	return input;
}
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

_Bool Validation(const char *string, const int length) {
	char set['9' + 1] = {0};
	for (int i = 0; i < length; ++i) {
		if (string[i] < '0' || string[i] > '9') {
			printf("bad input");
			return true;
		}
		if (set[(int)string[i]] == 0) {
			set[(int)string[i]] = 1;
		}
		else {
			printf("bad input");
			return true;
		}
	}
	return false;
}

void Swap(char *first, char *second) {
	char t = *first;
	*first = *second;
	*second = t;
}

void SwapPartOfString(int start, int end, char *string) {
	while (start < end) {
		char t = string[start];
		string[start] = string[end];
		string[end] = t;
		--end;
		++start;
	}
}

int Find(int start, int end, int stop, const char *string) {
	for (int i = start; i > end; --i) {
		if (stop < string[i]) {
			return i;
		}
	}
	return 0;
}

int FindSuffix(char *string, const int length) {
	int iterator = 0;
	for (int i = length - 1; i > 0; --i) {
		if (string[i] > string[i - 1]) {
			int index = Find(/*start*/length - 1,
					/*end*/i - 1,
					/*stop*/string[i - 1],
					/*string*/string);
			Swap(/*first*/&string[i - 1], 
					/*second*/&string[index]);
			SwapPartOfString(/*start*/i,
					/*end*/length - 1,
					/*string*/string);
			printf("%s\n", string);
			break;
		}
		iterator = i;
	}
	return iterator;
}

void Permute(char *string, const int length, int countPermutations) {
	while (countPermutations != 0) {
		int index = FindSuffix(/*string*/string,
			/*length*/length);
		if (index == 1) {
			return;
		}
		--countPermutations;
	}
}

int main() {
	char string[MAX_SIZE];
	int i = 0;
	while (scanf("%c", &string[i]) == 1) {
		if (string[i] == '\n') {
			string[i] = '\0';
			break;
		}
		++i;
		if (i == MAX_SIZE) {
			return 0;
		}
	}
	int lenString = strlen(string);
	int countPermutations = 0;
	if (scanf("%d", &countPermutations) != 1) {
		return 0;
	}
	bool isInvalid = Validation(/*string*/string,
			/*length*/lenString);
	if (isInvalid) {
		return 0;
	}
	Permute(/*string*/string,
			/*length*/lenString,
			/*countPermutations*/countPermutations);
	return 0;
}


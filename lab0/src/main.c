#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

long double CalcExp(long long a, long int degree) {
	long double result = 1.0;
	while (degree != 0) {
		if ((degree & 1) == 1) {
			result *= a;
			degree -= 1;
		}
		a *= a;
		degree /= 2;
	}
	return result;
}

void SplitByDot(const char *string, long int *countBeforeDot, long int *count) {
	int i = 0;
	bool beforeDot = true;
	*count = 0;
	*countBeforeDot = 0;
	while (string[i] != '\0') {
		if (string[i] == '.') {
			beforeDot = false;
		}
		++*count;
		++i;
		if (beforeDot) {
			++*countBeforeDot;
		}
	}
}


long double CalcValue(const char *num, int numSys) {
	long int len = 0, lenBeforeDot = 0;
	SplitByDot(/*string*/num,
			/*countBeforeDot*/&lenBeforeDot,
			/*count*/&len);
	long double exp = CalcExp(/*a*/numSys,
			/*degree*/lenBeforeDot);
	long double res = 0.0;
	for (int i = 0; i < len; ++i) {
		if (num[i] == '.') {
			continue;
		}
		int digit = 0;
		exp /= numSys;
		if (num[i] >= 'a') {
			digit = num[i] - 'a' + 10;
		}
		else if (num[i] >= 'A' && num[i] <= 'a') {
			digit = num[i] - 'A' + 10;
		}
		else {
			digit = num[i] - '0';
		}
		res += digit * exp;
	}
	return res;
}

void ReverseString(char *string, int len) {
	int i = 0;
	while (i < len) {
		char c = 0;
		c = string[i];
		string[i] = string[len];
		string[len] = c;
		++i;
		--len;
	}
}

void ConvertIntegerPart(long int integerPart, int numSys, const char *digits, char *result) {
	int i = 0;
	while (integerPart != 0) {
		result[i] = digits[integerPart % numSys];
		integerPart /= numSys;
		++i;
	}
	ReverseString(/*string*/result, /*len*/i - 1);
}

void ConvertFractionalPart(long double fractionalPart, int numSys, const char *digits, char *result) {
	result[0] = '.';
	char translationAccuracy = 13;	
	for (int i = 1; i < translationAccuracy; ++i) {
		fractionalPart *= numSys;
		int a = (int)fractionalPart;
		result[i] = digits[a];
		fractionalPart -= a;
	}
}

void ChangeToAnyNumberSystem(long double number, int numSys, char *result, const char *digits) {
	long int integerPart = (long int)number;
	long double fractionalPart = number - integerPart;
	char intResult[100] = "0";
	ConvertIntegerPart(/*integerPart*/integerPart,
			/*numSys*/numSys,
			/*digits*/digits,
			/*result*/intResult);
	char fractResult[100] = "";
	ConvertFractionalPart(/*fractionalPart*/fractionalPart,
			/*numSys*/numSys,
			/*digis*/digits,
			/*result*/fractResult);
	strcpy(result, intResult);
	strcat(result, fractResult);
}

bool CheckNumber(const char *number, int numSys, int *countDots, const char *digits) {
	if (number[0] == '.') {
		return true;
	}
	int lastDigit = 0, maxNumberLength = 13;
	for (int i = 0; i < maxNumberLength; ++i) {
		if (number[i] == '\0') {
			lastDigit = number[i - 1];
			break;
		}
		if ((number[i] < '0' || number[i] > digits[numSys - 1]) && (number[i] < 'A' || number[i] > digits[numSys - 1] + ('a' - 'A')) &&
                (number[i] < 'a' || number[i] > digits[numSys - 1]) && number[i] != '.') {
			return true;
		}
		if (number[i] == '.') {
			++*countDots;
			continue;
		}
	}
	if (lastDigit == '.' || *countDots > 1) {
		return true;
	}
	return false;
}

void PrintIntPart(const char *string) {
	int i = 0;
	while (true) {
		if (string[i] == '.') {
			break;
		}
		printf("%c", string[i]);
		++i;
	}
}

int main() {
	int b1 = 0, b2 = 0, countDots = 0;
	if (scanf("%d", &b1) != 1) {
		printf("error");
		return 0;
	}
	if (scanf("%d", &b2) != 1) {
		printf("error");
		return 0;
	}
	if ((b1 < 2 || b1 > 16) || (b2 < 2 || b2 > 16)) {
		printf("bad input");
		return 0;
	}
	const char digits[100] = "0123456789abcdef";
	char number[14];
	if (scanf("%13s", number) != 1) {
		printf("error");
		return 0;
	}
	bool isInvalid = CheckNumber(/*number*/number,
			/*numSys*/b1,
			/*countDots*/&countDots,
			/*digits*/digits);
	if (isInvalid) {
		printf("bad input");
		return 0;
	}
	long double res = CalcValue(/*num*/number,
			/*numSys*/b1);
	char answer[100] = "0";
	ChangeToAnyNumberSystem(/*number*/res,
			/*numSys*/b2,
			/*result*/answer,
			/*digits*/digits);
	if (countDots != 0) {
		printf("%s", answer);
	}
	else {
		PrintIntPart(/*string*/answer);
	}
    return 0;
} 


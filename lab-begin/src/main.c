#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool sum_and_check_elements(int count, long int *sum);

int main() {
	int num_of_elem;
	long int answer = 0;
	if (scanf("%d", &num_of_elem) != 1) {
		printf("error");
		return 0;
	}
	if (num_of_elem < 1 || num_of_elem > 10) {
		printf("bad input");
		return 0;
	}
	bool is_valid = sum_and_check_elements(/*count*/num_of_elem, /*sum*/&answer);
	if (is_valid) {
		printf("bad input");
		return 0;
	}
	if (answer < INT_MIN || answer > INT_MAX) {
		printf("overflow");
		return 0;
	} 
	printf("%ld", answer);
	return 0;
}

bool sum_and_check_elements(int count, long int *sum) {
	int num_of_entered_elem = 0;
	long int element = 0;
	while (scanf("%ld", &element) == 1) {
		num_of_entered_elem++;
		if (num_of_entered_elem > count || element > INT_MAX || element < INT_MIN) {
			return true;
		}
		*sum += element;
	}
	if (num_of_entered_elem < count) {
		return true;
	}
	return false;
}

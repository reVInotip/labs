#include "backpack/backpack.h"
#include "item/item.h"
#include <stdlib.h>
#include <stdio.h>

unsigned Max(unsigned a, unsigned b) {
	if (a > b) {
		return a;
	}
	return b;
}

int main(void) {
	unsigned countItems = 0, backpackSize = 0;
	if (scanf("%u %u", &countItems, &backpackSize) != 2) {
		printf("bad input");
		return EXIT_SUCCESS;
	}

	TBackpack backpack;
	InitBackpack(/*backpack*/&backpack, /*size*/backpackSize, /*countItems*/countItems);

	TItem* items = CreateItems(/*count*/countItems);	
	unsigned item = 1, currentCount = 0;
	while (currentCount != countItems) {
		unsigned weight = 0, cost = 0;
		if (scanf("%u %u", &weight, &cost) != 2) {
			printf("bad input");
			return EXIT_SUCCESS;
		}
		
		AddItem(/*items*/items, /*weight*/weight, /*cost*/cost, /*index*/currentCount);
		
		for (unsigned size = 1; size < backpack.Size; ++size) {
			if (size >= weight) {
				backpack.Pack[item * backpack.Size + size] =\
					Max(/*a*/backpack.Pack[(item - 1) * backpack.Size + size],
						/*b*/backpack.Pack[(item - 1) * backpack.Size + (size - weight)] + cost);
			} else {
				backpack.Pack[item * backpack.Size + size] = backpack.Pack[(item - 1) * backpack.Size + size];
			}
		}
		
		++item;
		++currentCount;
	}

	printf("%u\n", backpack.Pack[countItems * backpack.Size + backpackSize]);

	PrintItems(/*backpack*/backpack,
			/*items*/items,
			/*currentItem*/countItems,
			/*currentSize*/backpackSize);

	DestroyBackpack(/*backpack*/&backpack);
	DestroyItems(/*items*/items);

    return EXIT_SUCCESS;
}

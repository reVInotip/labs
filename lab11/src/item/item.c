#include "../backpack/backpack.h"
#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct TItem {
	unsigned Weight;
	unsigned Cost;
};

TItem* CreateItems(const unsigned count) {
	TItem* items = (TItem*)calloc(count, sizeof(TItem));
	assert(items);

	return items;
}

void AddItem(TItem* items, const unsigned weight, const unsigned cost, const unsigned index) {
	items[index].Weight = weight;
	items[index].Cost = cost;
}

void DestroyItems(TItem* items) {
	free(items);
}

void PrintItems(
	const TBackpack backpack,
	const TItem* items,
	unsigned currentItem,
	unsigned currentSize
) {
	if (backpack.Pack[currentItem * backpack.Size + currentSize] == 0) {
		return;
	} else if (backpack.Pack[(currentItem - 1) * backpack.Size + currentSize] ==\
			backpack.Pack[currentItem * backpack.Size + currentSize]) {
		PrintItems(backpack, items, currentItem - 1, currentSize);
	} else {
		PrintItems(backpack, items, currentItem - 1, currentSize - (items[currentItem - 1]).Weight);
		printf("%u %u\n", (items[currentItem - 1]).Weight, (items[currentItem - 1]).Cost);
	}
}	

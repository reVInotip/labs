#pragma once
#include "../backpack/backpack.h"

typedef struct TItem TItem;

TItem* CreateItems(const unsigned count);
void AddItem(TItem* items, const unsigned weight, const unsigned cost, const unsigned index);
void DestroyItems(TItem* items);
void PrintItems(const TBackpack backpack, const TItem* items, unsigned currentItem, unsigned currentSize);

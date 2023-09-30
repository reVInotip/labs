#pragma once

typedef struct TBackpack {
	unsigned* Pack;
	unsigned Size;
} TBackpack;

void InitBackpack(TBackpack* backpack, const unsigned size, const unsigned countItems);
void DestroyBackpack(TBackpack* backpack);

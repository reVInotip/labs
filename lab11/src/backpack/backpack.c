#include "backpack.h"
#include <stdlib.h>
#include <assert.h>

void InitBackpack(TBackpack* backpack, const unsigned size, const unsigned countItems) {
	unsigned* pack = (unsigned*)calloc((size + 1) * (countItems + 1), sizeof(unsigned));
	assert(pack);

	backpack->Pack = pack;
	backpack->Size = size + 1;
}

void DestroyBackpack(TBackpack* backpack) {
	free(backpack->Pack);
	backpack->Size = 0;
}

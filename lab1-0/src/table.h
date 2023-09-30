typedef struct TypeTable {
    char Data[256];
    int Len;
    int basicValue;
} table;

table CreateTable(int baseValue); 

void PushPair(table* array, unsigned char first, int second);

char GetElementByKey(const table* array, unsigned char key);

_Bool IsPairInTable(const table* array, unsigned char key);

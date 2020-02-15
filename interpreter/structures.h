typedef union {
    bool b;
    int i;
    float f;
    char *string;
    void *array;
} SnowflakeValue;

typedef enum {
    TYPE_BOOL,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_ARRAY
} SnowflakeType;

typedef struct {
    SnowflakeValue value;
    SnowflakeType type;
} SnowflakeVariable;

typedef struct {
    char instruction;
    SnowflakeVariable *first;
    SnowflakeVariable *second;
} Instruction;

typedef struct {
    int instruction_count;
    Instruction *instructions;
} AllInstructions;

typedef struct {
    SnowflakeVariable variable;
    void *next;
} VariableArrayItem;

typedef struct {
    int count;
    VariableArrayItem *items;
} VariableArray;

typedef struct {
    int index;
    int value;
    void *next;
} BankLabelItem;

typedef struct {
    int count;
    BankLabelItem *items;
} BankLabelList;

typedef struct {
    BankLabelList labels;
    BankLabelList banks;
    AllInstructions instructions;
} Program;
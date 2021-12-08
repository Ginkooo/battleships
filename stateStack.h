typedef enum {
    LOBBY,
    PLAYER_ONE,
    PLAYER_TWO,
} StateValue;

typedef struct State {
    StateValue value;
    State* prev;
} State;

typedef struct StateStack {
    State* top;

} StateStack;

StateStack init();

#ifndef STATESTACK_H
#define STATESTACK_H

typedef enum {
    STATE,
    PLAYER_ONE,
    PLAYER_TWO,
} StateValue;

typedef struct GameState {
    StateValue value;
    struct GameState* prev;
} GameState;

typedef struct StateStack {
    GameState* top;
    int size;

} StateStack;

StateStack init();
void push(StateStack* self, StateValue);
StateValue* pop(StateStack* self);
StateValue* peek(StateStack* self);
int topIsNotNullAndHasValue(StateStack* self, StateValue value);

#endif

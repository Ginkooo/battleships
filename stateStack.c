#include <stdlib.h>
#include "stateStack.h"
#include <stdio.h>
#include <stdlib.h>

StateStack init() {
    GameState* top = malloc(sizeof(GameState));
    StateStack ret;
    ret.top = top;
    ret.size = 0;
    return ret;
}

void push(StateStack* self, StateValue stateValue) {
    GameState state;
    state.value = stateValue;
    state.prev = NULL;
    if (self->size == 0) {
        *self->top = state;
        self->size++;
        return;
    }
    state.prev = self->top;
    *self->top = state;
    self->size++;
}

StateValue pop(StateStack* self) {
    GameState state = *self->top;
    self->top = state.prev;
    return state.value;
}

StateValue* peek(StateStack* self) {
    if (self->size == 0) {
        return NULL;
    }
    return &self->top->value;
}

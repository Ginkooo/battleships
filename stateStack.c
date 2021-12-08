#include <stdlib.h>
#include "stateStack.h"
#include <stdio.h>
#include <stdlib.h>

StateStack init() {
    StateStack ret = { .top = malloc(sizeof(GameState)), .size = 0 };
    return ret;
}

void push(StateStack* self, StateValue stateValue) {
    GameState state = { .value = stateValue, .prev = NULL };
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

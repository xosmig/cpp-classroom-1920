#pragma once

#include <iostream>

struct bot_state;

struct bot_environment {
    std::istream* in;
    std::ostream* out;
    std::ostream* err;
};

bot_state* init_bot();

void execute_command(bot_environment const* env, bot_state* state, char const* command);

void stop_bot(bot_state const* state);

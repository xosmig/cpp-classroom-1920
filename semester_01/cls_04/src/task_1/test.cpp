#include "helper_bot.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

struct string_bot_env : bot_environment {
    std::istringstream in_str;
    std::ostringstream out_str;
    std::ostringstream err_str;

    string_bot_env() : bot_environment{&in_str, &out_str, &err_str} {}

    void clear() {
        in_str.str("");
        in_str.clear();

        out_str.str("");
        out_str.clear();

        err_str.str("");
        err_str.clear();
    }
};

static void test_wrong_input() {
    bot_state* state = init_bot();
    string_bot_env env;

    {
        try {
            execute_command(nullptr, state, "");
            assert(false && "Execute command should not accept nullptr!");
        } catch (std::runtime_error const& err) {

        }

        try {
            execute_command(&env, nullptr, "");
            assert(false && "Execute command should not accept nullptr!");
        } catch (std::runtime_error const& err) {

        }

        try {
            execute_command(&env, state, nullptr);
            assert(false && "Execute command should not accept nullptr!");
        } catch (std::runtime_error const& err) {

        }
    }

    stop_bot(state);
}

static void assert_unknown_command(char const* cmd) {
    bot_state* state = init_bot();
    string_bot_env env;

    {
        execute_command(&env, state, cmd);
        assert(env.out_str.str().empty());
        assert(env.err_str.str() == std::string("Unknown command '") + cmd + "'!\n");
        env.clear();
    }

    stop_bot(state);
}

static void test_bot_hello() {
    assert_unknown_command("");
    assert_unknown_command("      ");
    assert_unknown_command("z");
    assert_unknown_command("    z   ");
    assert_unknown_command("1024");

    bot_state* state = init_bot();
    string_bot_env env;

    {
        execute_command(&env, state, "h");
        assert(env.out_str.str() == "Hello!\n");
        assert(env.err_str.str().empty());
    }

    {
        execute_command(&env, state, "    h    ");
        assert(env.out_str.str() == "Hello!\nHello!\n");
        assert(env.err_str.str().empty());
    }

    stop_bot(state);
}

int main() {
    test_wrong_input();
    test_bot_hello();

    return 0;
}
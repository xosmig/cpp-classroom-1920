#include <iostream>
#include <sstream>
#include <algorithm>

#include "expression.hpp"

//#define task_1
//#define task_1_5
//#define task_2
//#define task_3

using namespace expression;
using std::stringstream;
using std::string;

void assert(bool condition, string const& msg) {
    if (!condition) {
        throw std::runtime_error(msg);
    }
}

string clear_string(string s) {
    auto isbrace = [](char c) { return c == '(' || c == ')';};
    s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
    s.erase(std::remove_if(s.begin(), s.end(), isbrace), s.end());
    return s;
}

void task_1_smoke() {
#ifdef task_1
    {
        stringstream ss;
        Val val(10);

        val.print(ss);

        assert(ss.str() == "10", "Val(10) should be printed as \"10\" or \"10\"");
    }

    {
        stringstream ss;
        Expression const* val = new Add(new Val(10), new Val(20));

        val->print(ss);
        auto result = ss.str();

        assert(clear_string(result) == "10+20",
               "Add(Val(10), Val(20)) should be printed as \"10+20\"");

        delete val;
    }

    {
        stringstream ss;
        Expression const* val = new Mul(new Val(10), new Val(20));

        val->print(ss);
        auto result = ss.str();

        assert(clear_string(result) == "10*20",
               "Mul(Val(10), Val(20)) should be printed as \"10*20\"");

        delete val;
    }

    {
        stringstream ss;
        Expression const* val = new Mul(new Val(10), new Val(20));

        val->print(ss);
        auto result = ss.str();

        assert(clear_string(result) == "10*(20+30)",
               "Mul(Val(10), Add(Val(20), Val(30)) should be printed as \"10*(20+30)\"");

        delete val;
    }

    std::cout << "Smokes for task 1 passed" << std::endl;
#endif
}

void task_1_5_smoke() {
#ifdef task_1_5
    {
        Expression* val = new Val(10);

        assert(val->eval() == 10, "Val(10) should be evaled to 10");

        delete val;
    }

    {
        Expression* val = new Mul(new Val(10), new Val(20));

        assert(val->eval() == 200, "Mul(Val(10), Val(20)) should be evaled to 200");

        delete val;
    }

    std::cout << "Smokes for task 1.5 passed" << std::endl;
#endif
}

void task_2_smoke() {
#ifdef task_2
    {
        Expression* val = new Val(10);

        assert(val->eval(Context()) == 10, "Val(10) should be evaled to 10 in empty context");

        delete val;
    }

    {
        Context ctx;
        ctx.set_var("x", 100);

        Expression* var = new Var("x");
        assert(var->eval(ctx) == 100, "Var(x) should be evaled to 100 in context where x = 100");

        delete var;
    }

    std::cout << "Smokes for task 2 passed" << std::endl;
#endif
}

void task_3_smoke() {
#ifdef task_3
    {
        Expression* val = new Val(10);
        Expression* simplifiedVal = val->simplified(Context());

        assert(val->eval() == 10, "Val(10), simplified in empty context, should be evaled to 10");

        delete simplifiedVal;
        delete val;
    }

    {
        Context ctx;
        ctx.set_var("x", 100);

        Expression* var = new Var("x");
        Expression* simplifiedVar = var->simplified(ctx);

        assert(
            simplifiedVar->eval() == 100,
            "Var(x) simplified with context, where x = 100, should be evaled to 100"
        );

        delete simplifiedVar;
        delete var;
    }

    {
        Context ctx;
        ctx.set_var("x", 100);

        Expression* var = new Var("x");
        Expression* simplifiedVar = var->simplified(ctx);

        assert(
            simplifiedVar->eval() == 100,
            "Var(x) simplified with context, where x = 100, should be evaled to 100"
        );

        delete simplifiedVar;
        delete var;
    }

    {
        Context x_ctx;
        x_ctx.set_var("x", 2);

        Context y_ctx;
        y_ctx.set_var("y", 3);

        Expression* sum = new Add(new Var("x"), new Var("y"));
        Expression* simplifiedWithX = sum->simplified(x_ctx);
        Expression* simplifiedWithY = sum->simplified(y_ctx);

        assert(
            simplifiedWithX->eval(y_ctx) == 5,
            "x + y, simplified with {x = 2}, should be evaled to 5 in context {y = 3}"
        );

        assert(
            simplifiedWithY->eval(x_ctx) == 5,
            "x + y, simplified with {y = 3}, should be evaled to 5 in context {x = 2}"
        );

        delete simplifiedWithY;
        delete simplifiedWithX;
        delete sum;
    }

    std::cout << "Smokes for task 3 passed" << std::endl;
#endif
}


int main() {
    task_1_smoke();
    task_1_5_smoke();
    task_2_smoke();
    task_3_smoke();
}
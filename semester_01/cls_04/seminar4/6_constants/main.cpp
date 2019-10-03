#define ONE 1 // Bad way: C-Style

const int TWO = 2;

constexpr int THREE = 3; // also const

// Существует еще способы

int identity(int i) {
    return i;
}

int main() {

    identity(ONE);

    identity(TWO);

    identity(THREE);

    // Don't use #define
    // #Reason1: Scopes
    {
        #define SOME_CONST 42
    }
    identity(SOME_CONST); // access out of scope

    // #Reason2: magic numbers when debugging

    return 0;
}

// References:
// 1) http://www.stroustrup.com/bs_faq2.html#macro
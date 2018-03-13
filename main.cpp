#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>

using BraceChecker = bool(const std::string&);

static const char *GOOD_CASES[] = {
    "", "()", "{}", "[]",
    "abc", "a(b)c", "a{bb}cdd", "[]addd",
    "a(b([]c))a", "(b[{}d])aa", "([a(({b{}}dd))d]a)",
    "a(b([]c))a(b[{}{[][]}d])aa"
};

static const char *BAD_CASES[] = {
    "(", ")", "[[", "}", "([]", "({[}])", ")(){}", "a(b([]c))a(b[{}}{]}d])aa"
};

void TestBraceChecker(BraceChecker * checker) {
    for(auto good : GOOD_CASES) {
        if (!checker(good))
            throw std::runtime_error("Brace checker failed on good case: " + std::string(good));
    }
    for (auto bad : BAD_CASES) {
        if (checker(bad))
            throw std::runtime_error("Brace checker succeeded on bad case: " + std::string(bad));
    }
}

bool CheckBraces(const std::string & str) {
    std::stack<char> brace_stack;

    for (auto c : str) {
        switch (c) {
        case '(':
            brace_stack.push(')');
            break;
        case '[':
            brace_stack.push(']');
            break;
        case '{':
            brace_stack.push('}');
            break;
        case ')':
        case ']':
        case '}':
            if (brace_stack.empty())
                return false;
            if (c != brace_stack.top())
                return false;
            brace_stack.pop();
            break;
        default:
            break;
        }
    }
    return brace_stack.empty();
}

int main()
{
    try {
        TestBraceChecker(CheckBraces);
        std::cout << "Successfully tested CheckBraces() function!" << std::endl;


    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

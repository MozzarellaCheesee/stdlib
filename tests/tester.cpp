#include <iostream>

// ─── Test framework ──────────────────────────────────────────────────

struct TestRunner {
    int passed = 0;
    int failed = 0;

    void run(const char* name, auto fn) {
        try {
            fn();
            ++passed;
            std::cout << "  [PASS] " << name << "\n";
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "  [FAIL] " << name << " — " << e.what() << "\n";
        } catch (...) {
            ++failed;
            std::cout << "  [FAIL] " << name << " — unknown exception\n";
        }
    }

    void summary() const {
        std::cout << "\n---------------------------------\n";
        std::cout << "  Total:  " << passed + failed << "\n";
        std::cout << "  Passed: " << passed << "\n";
        std::cout << "  Failed: " << failed << "\n";
        std::cout << "-----------------------------------\n";
    }

    int exit_code() const { return failed > 0 ? 1 : 0; }
};

#define ASSERT(expr) \
    if (!(expr)) throw std::runtime_error("Assertion failed: " #expr)

#define ASSERT_THROWS(expr) \
    { bool threw = false; try { expr; } catch (...) { threw = true; } \
    if (!threw) throw std::runtime_error("Expected exception: " #expr); }

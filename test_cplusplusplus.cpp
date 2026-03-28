// C+++ test file
let x = 42;
var y = "Hello, C+++";

defer {
    // Cleanup code
}

// Test pipe operator
let result = 10 |> [](int n) { return n * 2; };

// Test match statement
match (x) {
    case 42: {
        // Handle 42
        break;
    }
    default: {
        // Handle other values
        break;
    }
}

// Test interface
interface MyInterface {
    virtual void doSomething() = 0;
}

class MyClass : public MyInterface {
public:
    void doSomething() override {
        // Implementation
    }
};

int main() {
    // Test error propagation
    let value = someFunction() ?? 0;
    return 0;
}

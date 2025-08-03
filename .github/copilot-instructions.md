# OpenGraph Copilot Instructions

This file contains coding guidelines and conventions for AI assistants working on the OpenGraph project.

## Quick Reference

### Key Principles
- Use `swift-testing` framework with `#expect` macro (not XCTest)
- Follow OpenGraph C++ and Swift interop patterns
- Trim trailing whitespaces automatically
- Use 4-space indentation consistently

## Testing Guidelines

### Testing Framework

- Use the `swift-testing` framework with the `#expect` macro for all test assertions
- Import testing framework with: `import Testing`
- Do NOT use XCTest framework unless specifically required for compatibility

### Test Structure

```swift
import Testing

struct OpenGraphTests {
    @Test
    func functionality() {
        let value = SomeType()
        
        #expect(value.property == expectedValue)
        #expect(value.method() == expectedResult)
    }

    @Test
    func errorConditions() {
        #expect(throws: SomeError.self) {
            try riskyOperation()
        }
    }
}
```

### Test Conventions

- **Do NOT write any comments in test case body** - keep test code clean and self-explanatory
- Use descriptive test function names that clearly indicate what is being tested
- Group related tests using `// MARK: -` sections
- Use `#expect` for all assertions instead of XCTest assertions
- Prefer multiple focused tests over one large test
- Do not add test prefix to test function names (e.g., `testFunctionality` should be `functionality`)
- Use `@Test` attribute for test functions

## Code Organization

### File Structure
- Use `// MARK: -` to separate different topics and sections within files
- Organize code logically with clear separation of concerns
- Place imports at the top, followed by type definitions, then implementations

### Example MARK Usage
```swift
// MARK: - A

...

// MARK: - B

...

// MARK: - C

...
```

## Swift Coding Style

### Access Control Hierarchy

1. `public` - External API surface
2. `internal` - Module-internal APIs (default and should be omitted if not needed)
3. `private` - Implementation details

### Naming Conventions

- Follow Swift API Design Guidelines
- Use descriptive names that clearly indicate purpose
- Prefer full words over abbreviations
- Use camelCase for variables, functions, and properties
- Use PascalCase for types, protocols, and cases

### Code Formatting Rules

- **Automatically trim trailing whitespaces including whitespace-only lines**
- Use consistent indentation (4 spaces, not tabs)
- Place opening braces on the same line as the declaration
- Use proper spacing around operators and after commas
- Align code vertically when it improves readability
- Maximum line length: 120 characters (soft limit)

## C++ Coding Style

### OpenGraphCxx Guidelines

- Follow existing OpenGraph C++ patterns and conventions
- Use `OG_INLINE` and `OG_CONSTEXPR` macros for inline and constexpr functions
- Use `OG_NOEXCEPT` for exception specifications
- Maintain compatibility with existing OpenGraph APIs
- Use proper header guards with project-specific naming

### Memory Management

- Use RAII principles for resource management
- Prefer smart pointers and custom deleters for automatic cleanup
- Use `ptr<T>` template for OpenGraph-specific pointer management
- Implement proper validation and assertion mechanisms

### Template Usage

```cpp
template <typename T>
class ptr {
    // Implementation following OpenGraph patterns
};
```

## Architecture Patterns

### OpenGraph Compatibility
- Maintain API compatibility with existing OpenGraph functionality
- Use similar naming conventions and parameter patterns
- Implement protocols and extensions that mirror OpenGraph's design

### Module Organization
- Keep related functionality in appropriate modules
- Use clear module boundaries between OpenGraphCxx and Swift layers
- Avoid circular dependencies between modules

### C++/Swift Interop
- Use proper bridging headers for C++ integration
- Ensure memory safety across language boundaries
- Handle exceptions and errors appropriately at boundaries

## Documentation

### Code Comments
- Write clear, concise comments for complex logic
- Use documentation comments (`///`) for APIs documentation
- Avoid obvious comments that don't add value
- Keep comments up-to-date with code changes

### API Documentation
```swift
/// A brief description of what this function does.
/// 
/// - Parameter value: Description of the parameter
/// - Returns: Description of the return value
/// - Throws: Description of potential errors
func someFunction(value: String) throws -> Int {
    // Implementation
}
```

## Performance Considerations

- Optimize memory allocation patterns using OpenGraph's table/page system
- Use lazy initialization for expensive computations
- Consider memory management and avoid retain cycles
- Optimize for common use cases while maintaining flexibility
- Profile memory usage patterns in graph operations

## Dependencies and Imports

### Swift Files
- Minimize external dependencies
- Use conditional compilation for platform-specific code
- Import only what is needed
- Organize imports alphabetically within groups

### C++ Files
- Use proper header inclusion guards
- Include OpenGraph base headers first
- Follow dependency order in include statements
- Use forward declarations when possible

## Platform Compatibility

- Support multiple Apple platforms (iOS, macOS, watchOS, tvOS, visionOS)
- Use availability annotations when using platform-specific APIs
- Test on supported platform versions
- Use feature detection rather than version checking when possible
- Handle platform differences in C++ code using preprocessor directives

## Memory and Data Management

### OpenGraph Patterns
- Use `data::table` for memory region management
- Implement proper page allocation and deallocation
- Use `ptr<T>` for type-safe offset-based pointers
- Follow OpenGraph's zone-based memory organization

### Validation and Assertions
- Use `assert_valid` methods for pointer validation
- Implement proper precondition checking
- Use OpenGraph's assertion macros consistently
- Handle edge cases gracefully

---

## Troubleshooting

### Common Issues
- **Build errors**: Check C++/Swift bridging and header paths
- **Test failures**: Ensure using `#expect` not XCTest assertions
- **Memory issues**: Verify proper pointer validation and table usage
- **Interop problems**: Check Swift/C++ type compatibility

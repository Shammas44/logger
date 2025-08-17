# Logger

A simple C library for logging messages with different severity levels at runtime.

---

## Features

* **Categorized Logging**: Log messages as errors, warnings, info, or success.

* **Compile-time Macros**: Use simple macros like `LOG_ERROR` and `LOG_INFO` to automatically capture file and line information.

* **Runtime Modes**: Switch between `default` (verbose) and `silent` logging modes.

* **Last Log Retrieval**: Get the last logged message for debugging or testing purposes.

---

## How to Build

This project uses a `Makefile` to build a static library (`.a`) and a shared library (`.so`).

### Dependencies

Before building, ensure you have `gcc` and `make` installed.

### Standard Build

To build the static and shared libraries, run `make` from the project root.

```bash
make
```

### Build with Debugging Symbols

For development, you can build with debugging symbols by setting the `OPTION` variable.

```bash
make OPTION=dev
```

### Building for CI

The project is configured to run tests in a CI environment (e.g., GitHub Actions) using a specific `OPTION` value that enables position-independent code (PIC) for shared libraries. You can manually run this command:

```bash
make OPTION=test
```

---

## How to Install

The `Makefile` includes `install` and `uninstall` targets to place the compiled libraries and header files in the correct system directories (`/usr/local/lib` and `/usr/local/include`).

**Install the libraries:**

```bash
sudo make install
```

**Uninstall the libraries:**

```bash
sudo make uninstall
```

---

## How to Use

To use the `logger` in your C project, you need to include the header and link against the shared library.

1.  **Include the header file**:

    ```c
    #include <logger/logger.h>
    ```

2.  **Link against the library**: When compiling your application, link with the `-l` flag and specify the library's location if it's not in a standard path.

    ```bash
    gcc your_app.c -o your_app -l logger
    ```

3.  **Use the logging functions**:

    ```c
    #include <logger/logger.h>
    #include <stdio.h>

    int main() {
        LOG_INFO("Application started.");
        LOG_WARNING("This is a warning.");
        LOG_ERROR("Something went wrong!");
        
        // Example of a function that might use a log
        some_other_function();

        return 0;
    }
    ```

---

## Testing

The project's `Makefile` includes a `test` target to build and run the unit tests using the Criterion C test framework.

**Running tests:**

```bash
make OPTION=test run_test
```

---

## Important Considerations

* **Compiler Flags**: The `Makefile` includes checks for `OPTION=test` to add the `-fPIC` flag, which is crucial for building shared libraries on Linux. Ensure your build environment is configured correctly.

* **Dynamic Linking**: When you run an application that links dynamically to `lilogger.so`, the system needs to know where to find the shared library at runtime. Running `sudo make install` places it in `/usr/local/lib`, a standard location. If you install it elsewhere, you may need to add the path to your `LD_LIBRARY_PATH` environment variable.

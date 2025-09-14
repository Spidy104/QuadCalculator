# QuadCalculator

A **quadratic equation solver** written in modern C++. It supports both **real** and **complex** coefficients and computes roots using the **quadratic formula**.

---

## 📖 The Quadratic Equation

A quadratic equation is of the form:

$$ax^2 + bx + c = 0, \quad a \neq 0$$

The discriminant is given by:

$$\Delta = b^2 - 4ac$$

The roots are then:

$$x_{1,2} = \frac{-b \pm \sqrt{\Delta}}{2a}$$

### Root Types

* If $\Delta > 0$: two distinct real roots.
* If $\Delta = 0$: one real repeated root.
* If $\Delta < 0$: two complex conjugate roots.

---

## 🚀 Features

* Compute **real roots** and **complex roots** of any quadratic equation.
* Accept coefficients in both **real** and **complex** form.
* Support for **square root notation** in input (e.g. `sqrt(3)`, `2sqrt(5)`, `-sqrt(7)`).
* Colored console output for clarity (on supported terminals).
* Cross-platform compatibility (Linux, macOS, Windows).

---

## 🔧 Build Instructions

### Requirements

* A C++20 compiler (GCC ≥ 10, Clang ≥ 10, MSVC ≥ 2019)
* CMake ≥ 3.16

### Steps

```bash
git clone https://github.com/yourname/QuadCalculator.git
cd QuadCalculator
mkdir build && cd build
cmake ..
cmake --build .
```

This will produce an executable named `QuadCalc` (or `QuadCalc.exe` on Windows).

---

## 🖥️ Usage

### Display Help

```bash
./QuadCalc -h
```

### Solve with Real Coefficients

**Mode:** `-r`

```bash
./QuadCalc -r 1 -3 2
```

**Output:**
```
The discriminant is: 1
Root 1 : (2.00)
Root 2 : (1.00)
```

**Supports square root notation:**

```bash
./QuadCalc -r 1 sqrt(2) 3
```

### Solve with Complex Coefficients

**Mode:** `-cc`

Arguments are written as `real,imag`. Example:

```bash
./QuadCalc -cc 1,2 3,4 5,6
```

**Output:**
```
The discriminant is: (-28.00 + 44.00i)
Root 1 : (-0.23 + 0.69i)
Root 2 : (-2.77 - 1.69i)
```

You can also use square root syntax inside components:

```bash
./QuadCalc -cc "2,sqrt(3)" "3,4" "5,6"
```

⚠️ **Note for zsh/fish users**: Quote arguments containing parentheses, e.g. `"sqrt(3)"`.

---

## 📂 Input Syntax

### Real Coefficients (`-r`)

* **Numbers:** `1`, `-3`, `2.5`
* **Square roots:** `sqrt(3)`, `2sqrt(5)`, `-sqrt(7)`

### Complex Coefficients (`-cc`)

* **Format:** `real,imag`
* **Examples:**
    * `1,2` → $1 + 2i$
    * `-3,0` → $-3$
    * `0,-4` → $-4i$
* Both real and imaginary parts support `sqrt(...)`.
* **Shell-friendly form (alternative):**

```bash
./QuadCalc -cc 1 2 3 4 5 6   # treated as (1+2i), (3+4i), (5+6i)
```

---

## 📘 Examples

### Example 1 — Real Roots

```bash
./QuadCalc -r 1 -5 6
```

**Equation:** $x^2 - 5x + 6 = 0$  
**Discriminant:** $\Delta = 25 - 24 = 1$  
**Roots:** $x_1 = 3, x_2 = 2$

### Example 2 — Complex Roots

```bash
./QuadCalc -r 1 2 5
```

**Equation:** $x^2 + 2x + 5 = 0$  
**Discriminant:** $\Delta = 4 - 20 = -16$  
**Roots:** $-1 \pm 2i$

### Example 3 — Complex Coefficients

```bash
./QuadCalc -cc 1,1 2,0 3,0
```

**Equation:** $(1+i)x^2 + 2x + 3 = 0$  
**Discriminant:** $(-10.00 + 12.00i)$  
**Roots:** $(-0.67 + 1.39i), (-1.33 - 0.39i)$

### Example 4 — Square Root Coefficients

```bash
./QuadCalc -r 1 sqrt(2) -3
```

**Equation:** $x^2 + \sqrt{2}x - 3 = 0$  
**Discriminant:** $\Delta = 2 + 12 = 14$  
**Roots:** $x_1 \approx 1.29, x_2 \approx -2.00$

---

## 📊 Visual Guide: Root Behavior

```
Real Discriminant (Δ):
   Δ > 0:  ●────────●     (two distinct real roots)
   Δ = 0:     ●           (one repeated real root)
   Δ < 0:     ●           (complex conjugate pair)
           ╱     ╲
          ●       ●       (on complex plane)
```

---

## 🛠️ Project Structure

```
QuadCalculator/
├── includes/
│   ├── ColorMod.h
│   ├── Complex.h
│   ├── PPrintter.h
│   └── PPrintter.cpp   # currently in includes (odd)
├── src/
│   └── QuadCalculator.cpp
├── CMakeLists.txt
|── .gitignore
└── README.md


```



## 🔍 Technical Details

### Numerical Precision

* Uses `std::complex<double>` for all calculations
* Handles edge cases like $a = 0$ (linear equation)
* Robust square root parsing with error checking

### Algorithm

1. **Parse input** coefficients (real or complex, with sqrt support)
2. **Validate** that $a \neq 0$
3. **Calculate discriminant** $\Delta = b^2 - 4ac$
4. **Compute roots** using quadratic formula
5. **Format output** with appropriate precision

### Error Handling

* Invalid coefficient formats
* Non-quadratic equations ($a = 0$)
* Malformed square root expressions
* Shell escaping issues

---

## 🌟 Advanced Usage

### Batch Processing

Create a script to solve multiple equations:

```bash
#!/bin/bash
echo "Solving multiple quadratics:"
./QuadCalc -r 1 -2 1    # (x-1)²
./QuadCalc -r 1 0 -4    # x² - 4
./QuadCalc -r 1 1 1     # x² + x + 1
```

### Integration with Other Tools

Pipe results to analysis tools:

```bash
./QuadCalc -r 1 -3 2 | grep "Root" | awk '{print $3}'
```

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes and add tests
4. Commit your changes (`git commit -m 'Add some amazing feature'`)
5. Push to the branch (`git push origin feature/amazing-feature`)
6. Open a Pull Request

---

## 📚 References

* [Quadratic Equation — Wikipedia](https://en.wikipedia.org/wiki/Quadratic_equation)
* [Complex Numbers — Wikipedia](https://en.wikipedia.org/wiki/Complex_number)
* [Numerical Recipes in C++](http://numerical.recipes/)

---

## 📄 License

MIT License—see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

* Thanks to the C++ community for modern language features
* Inspired by classic mathematical computation tools
* Built with ❤️ for students and engineers

---

✨ **With this README, your QuadCalculator is now a clear guide and reference for both mathematics and code!**
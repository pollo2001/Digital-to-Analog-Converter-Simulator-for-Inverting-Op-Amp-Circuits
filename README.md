# D/A Converter Calculator ⚡

This project implements a digital-to-analog (D/A) converter calculator for an **inverted 741 op-amp amplifier**. Users input digital bits and resistor values, and the program outputs corresponding analog voltages in a truth table.  

## Features 🛠️
- Models voltage input sources with associated resistors  
- Calculates output voltages based on input bit status  
- Recursive design for truth table generation  
- Easily expandable for different amplifier configurations and calculations  
- Serves as a calculator for analog outputs and amplification math  

## Deliverables 📂
1. `d2aconverter.cpp` implementing the logic  
2. Vector-based truth table output  
3. Flexible code structure for extending calculations  

## Instructions 📝
- Compile and run with any standard C++ compiler  
- Enter the number of bits, the feedback resistor, ON voltage, and each input resistor  
- Outputs a voltage table for all input combinations  

## License 📝
MIT License – see the [LICENSE](LICENSE) file for details.

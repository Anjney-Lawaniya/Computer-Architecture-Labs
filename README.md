# Overview
1. This repo contains multiple lab assignments of the Course CS2206-Computer Architecture taught at Indian Institute of Technology, Patna in the Spring of 2026.
2. There are wide varieties of topics covered to help you get started with the basic understanding of Computer Architecture and have a strong foundation practically.
3. There are four type of files:
    * **Logisim Files** - These files are ciruit diagrams that can be run on logisim software only. You can download this software from the folder `00_Helper_Files` of this repo or the [official site](https://cburch.com/logisim/download.html). There are two versions: `2.7.1` and `logisim-evolution`. All the circuits were made on `Logisim 2.7.1`. However, with minor tweaks, they can be made compatible for later versions too.
    * **MARS Files** - These are MIPS code files with extension `.asm`.  `MARS emulator` is needed to run these files. This software can be downloaded from the same folder as Logisim software or the [official site](https://dpetersanderson.github.io/)
    * **C Files** - *CPUlator*, a web-based emulator, allows you to compile the C code directly into architecture-specific assembly (such as MIPS or Nios II), giving you a live, cycle-by-cycle view of how your high-level logic translates into machine instructions, maps to memory, and manipulates physical registers. You can run these simulations directly in your browser via the [official CPUlator website](https://cpulator.01xz.net/).
    * **.s Files** - These are native assembly language files. Unlike the MARS-specific `.asm` files, these follow the standard GNU Assembler syntax. They are generally designed for direct execution on actual hardware boards or for cross-compilation toolchains. These files can be assembled and linked using the GNU Compiler Collection (`gcc`) or the GNU Assembler (`as`).
##  ***More details and resources with clearer instructions are in the respective folders. If still stuck, feel free to reach out to me via [email](mailto:anjneylawaniya@gmail.com).***

# Lab Wise Description

## Lab 1 - Arithmetic Modules: Adder
In this lab, we start from the very bottom—transistors—and build our way up to a fully functional arithmetic module. If you've ever wondered how physical electrical switches actually compute math, this is where it happens.

**Primary Goals:**
* **Transistor-Level Logic:** We kick things off by building basic CMOS logic gates (Inverter, NAND, and XOR) completely from scratch using raw P-type and N-type transistors. 
* **The Gate Library:** Using our newly minted transistor gates, we construct the essential arithmetic building blocks: the **Half Adder** and the **Full Adder**.
* **Scaling Up (32-bit Adder):** Here is where things get serious. We cascade our custom gate library to design a complete 32-bit adder capable of handling real integer mathematics.
* **The Ultimate Challenge (5-Number Addition):** The final boss of this assignment. We extend our architecture to support the simultaneous addition of 5 distinct numbers, complete with an appropriate test bench to verify that our logic holds up under pressure.

**Primary Tool Used:** `Logisim`.

## Lab 2 - Floating-Point Adder Architecture (16-bit IEEE-754)
This lab tackles the intricate logic required to process fractional numbers using the IEEE-754 standard. If you want to understand how a CPU handles scientific calculations and precise decimals, this is the blueprint.

**Primary Goals:**
* **The 16-Bit IEEE-754 Format:** We break down the standard into its physical hardware components: 1 Sign bit, 5 Exponent bits, and 10 Fraction (Mantissa) bits.
* **The Hardware Algorithm:** Designing the step-by-step logic to add two floating-point numbers. This includes extracting the hidden bits, dynamically equalizing the exponents (via hardware bit-shifting), and executing the final integer addition on the aligned mantissas.
* **Edge Case Architecture:** Real processors crash if they can't handle extreme numbers. This lab documents how the architecture manages hardware limits, including minimum/maximum representable values, true zero, and non-representable special cases (like NaN or Infinity).
* **Circuit Schematics & Execution Traces:** Includes the high-level block schematic of the datapath and detailed manual step-by-step traces proving the alignment and addition logic works flawlessly before touching the simulator.

**Primary Tool Used:** `Logisim`.

## Lab 3 - Arithmetic and Logic Unit (ALU) and Register File
This lab focuses on designing the core computational and storage components of a processor. We construct a multi-functional Arithmetic and Logic Unit (ALU) and a comprehensive 32-bit Register File, ultimately integrating them to simulate a fundamental datapath execution cycle.

**Primary Goals:**
* **Multi-Function ALU Design:** Implementing a custom N-bit ALU capable of executing specific hardware-level instructions (AND, OR, ADD, SUB, Set-Less-Than). The operations are dynamically routed using a custom 3-bit control signal ($F_{2:0}$) and internal multiplexing.
* **32x32 Register File Architecture:** Engineering a robust storage module containing 32 independent 32-bit registers. This requires complex wiring using decoders for the single write port and massive multiplexers for the dual read ports.
* **Datapath Integration & Testing:** Combining the ALU and the Register File into a single cohesive circuit. This serves as a miniature execution stage where operands are fetched from specific registers, processed by the ALU based on the control bits, and successfully written back to memory.

**Primary Tool Used:** `Logisim`

## Lab 4 - MIPS Programming and System Calls
This lab bridges the gap between digital logic and computer science by introducing you to pure MIPS Assembly Language. Instead of placing physical gates, you will now write the low-level machine instructions that directly control the datapath and manipulate memory. 

**Primary Goals:**
* **The MARS Simulator:** Getting hands-on with the MIPS Assembler and Runtime Simulator. You will learn how to load bare-metal programs, execute them step-by-step, and monitor live hex changes inside the CPU registers and memory locations.
* **System Calls (Syscalls):** How does a processor actually talk to the outside world? We explore MIPS system services to handle basic I/O operations—reading user input, printing strings/integers, and safely terminating processes using specific `$v0` codes.
* **C to Assembly Translation:** Demystifying the compiler. We break down high-level C logic (like algebraic equations) and translate it manually into optimized MIPS instruction sequences.
* **Memory Mapping & Little Endianness:** A deep dive into the `.data` segment. You will map exactly how `.byte`, `.half`, `.word`, and `.asciiz` data types are stored in physical memory at the byte level, paying strict attention to memory alignment (`.align`) and Little-Endian byte ordering.

**Primary Tool Used:** `MARS`.

## Lab 5 - C to Assembly Translation
This lab bridges the highest levels of software engineering with the lowest levels of hardware execution. We strip away the magic of high-level programming and manually translate complex C code into strict, cycle-by-cycle MIPS Assembly. If you want to know exactly how a recursive function or a nested `for` loop physically executes in memory, this is the lab.

**Primary Goals:**
* **Pseudo-Instructions vs. Bare Metal:** Unpacking the assembler's secrets. We dissect how programmer-friendly pseudo-instructions (like `li`, `move`, and `ble`) are physically expanded into native, 32-bit machine code instructions.
* **Control Structures & Pointer Arithmetic:** Manually translating C `for` loops, `if/else` statements, and complex array manipulations (e.g., `A[i] = A[i-2] + b[i]`). This requires calculating exact memory offsets and managing base addresses dynamically.
* **The Call Stack & Recursion:** Engineering robust function protocols. You will learn to manage the stack pointer (`$sp`), preserve the return address (`$ra`) across nested calls, and successfully execute a fully recursive Factorial algorithm in assembly.
* **Macros vs. Subroutines:** Exploring compile-time optimizations. We build custom MIPS macros (like `print_string`) to automate repetitive code generation and compare their execution overhead directly against standard runtime subroutines (`jal`).
* **Advanced Memory Alignment:** A deeper dive into how the assembler packs mixed data types (`.byte`, `.half`, `.word`, `.double`) into physical memory, enforcing strict alignment boundaries.

**Primary Tool Used:** `MARS` / `CPUlator`.

## Lab 6 - MIPS RISC Processor Datapath Design
All the isolated hardware modules we built in the previous weeks are finally brought together. In this lab, we graduate from building individual components to engineering a complete, functioning Single-Cycle MIPS Processor. If you want to see exactly how a CPU fetches, decodes, and executes a line of code in a single clock tick, this is the master blueprint.

**Primary Goals:**
* **Data Memory Integration:** Designing and verifying the physical RAM block. You will implement clock-synchronized read and write operations, ensuring your processor can safely store and retrieve data.
* **Instruction-Specific Routing:** Before building the massive final CPU, we break down the datapath by instruction type. You will trace and wire the exact logic paths required for R-Type (`add`, `or`), I-Type (`addi`, `sw`), and Branching (`beq`) instructions as separate library components.
* **The Single-Cycle Architecture:** The grand finale. We integrate your custom ALU (from Lab 3), the 32x32 Register File, Instruction Memory, and Data Memory into one unified top-level schematic. You will route the critical control lines, sign-extension units, and multiplexers required to make the entire processor run autonomously.

**Primary Tool Used:** `Logisim`.

## Lab 7 - MIPS RISC Processor Single Cycle Design
This lab represents a major milestone: the completion of a fully autonomous, Single-Cycle MIPS Processor. We upgrade the basic datapath from the previous lab by engineering the "brain" of the CPU—the Control Unit. By decoding instruction opcodes and functionally driving every multiplexer and memory module, the processor can now execute a complete set of fundamental programs.

**Primary Goals:**
* **The Control Unit:** Designing the central decoding logic that reads 32-bit machine instructions and generates the precise control signals (e.g., `MemtoReg`, `RegWrite`, `ALUSrc`, `Branch`) required to route data flawlessly through the circuit.
* **Full Instruction Set Architecture (ISA) Support:** Expanding the hardware to natively support a comprehensive suite of instructions. This includes memory access (`lw`, `sw`), arithmetic/logic operations (`add`, `sub`, `and`, `or`, `addi`, `slt`), and complex control flow/branching (`beq`, `j`, `jr`, `jal`).
* **Algorithmic Hardware Verification:** The ultimate proof of concept. You will write custom assembly programs from scratch—such as algorithms to compute the sum of *n* numbers or find the maximum value in a dataset—and run their machine code directly on your Logisim datapath to verify architectural correctness.

**Primary Tool Used:** `Logisim`.

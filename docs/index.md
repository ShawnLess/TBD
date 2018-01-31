![TBD Architecture]({{ site.baseurl }}/assets/user_images/TBD.png)

# Why TBD?
**A**pplicaton **S**pecific **I**nstruction-set **P**rocessors (**ASIP**) are processors that are highly tailored 
to specific domain and thus gains huge efficiency while maintains the progammbility. 

Due to the emerging computation workloads like the baseband processing for LTE, neural network processing for Deep Learning,
and High resulotion image processing etc, ASIP is becoming very popular.

Many companies began to develope they own ASIPs, like the Google TPU&amp;IPU and other numerous AI chips. 
Nevertheless, building a ASIP toolchain from scratch is time consuming 
and because ASIPs are highly application dependend and their ISA are likely change frequently, maitaining the 
seperated tools would also require great effort.

Thus, **generating toolchain from single ISA specification** is very promising.
There are already commerial products that can generate toolchains and even RTL: 

|  tool     |   company     | Assembler | Linker | Compiler | ISS      | OpenSource | Reference |   
|-----------|---------------|-----------|--------|----------|----------|------------|-----------|
|  LISA     |   Synopsys    | &#10003;  |&#10003;| 3rd Party| &#10003; | &#10005;   | [Processor Designer](https://www.synopsys.com/designware-ip/processor-solutions/asips-tools.html) |
|  nML      |   Synopsys    | &#10003;  |&#10003;| &#10003;  | &#10003; | &#10005;   | [ASIP Designer](https://www.synopsys.com/dw/ipdir.php?ds=asip-designer) |
|  CodAL    |   Codasip     | &#10003;  |&#10003;| &#10003;  | &#10003; | &#10005;   | [CODIX](https://www.codasip.com/custom-processor/) |
|**TBD**    |               | &#10003;  |&#10003;| &#10003;  | &#10003; | &#10003;   |          |

But none of these commerial tools are free avaliable. In addition, all of the commerial tools are based 
on property tools, make it hard to do furthur integration and extension.

TBD is an open source tool that generates toolchains for ASIP. It has following advantages:
1. **Single specification** and complete toolchain, easy for maintaining
2. **Open source**.
3. **Explicit Backend**: Based on popular tools like [LLVM](http://www.llvm.org) and [Gem5](http://www.gem5.org/Main_Page), 
lower learning curve and easy to extend

# Table of content

|  Version  | Descrition                                | Document                 |
|-----------|--------------------------                 |-----------               |
|  v0.0.0   | Clean LLVM 5.0.1 source                   | [subdocs/v0-0-0.md](subdocs/v0-0-0)   |
|  v0.0.1   | LLVM Target 'tbd'                         | [subdocs/v0-0-1.md](subdocs/v0-0-1)   |
|  v0.0.2   | Target Description (Tablegen as .td) and AsmInfo| [subdocs/v0-0-2.md](subdocs/v0-0-2)   |
|  v0.0.3   | An Simple Instruciton and InstPrinter     | [subdocs/v0-0-3.md](subdocs/v0-0-3)   |

## Really To Be Done 1:
1. Added a target in the latest stable LLVM-MC, with single instruction assemble/disassemble ability.
2. Added a target in the latest stable LLVM-LLD, with single relocation relocation ability.
3. Added a target in the latest stable Gem5, with single instruction support 

## Really To Be Done 2:
1. Come up with a 'mini-subset' RISC-V instruction set for concept demonstration
2. Come up with a 'TBD language' that is capable of describe the need information
3. Working on the 'prototype' of the TBD compiler

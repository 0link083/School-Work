using System;

namespace prototypeASM
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            UVSIM sim = new UVSIM(@args[0]); // read the arguments from command line, the argument should be a filename containing assembly code.
            VM vm = new VM(sim);
            while (sim.programCounter <= 100)
            {
                if (sim.programCounter >= sim.memory.Length || vm.ExecuteOpCode(sim.memory[sim.programCounter]) != 0)
                {
                    return;
                }
                sim.programCounter += 1;
                vm.MEMDUMP();
            }
        }
    }
    public class UVSIM {
        public string[] memory;
        public string accumulator;
        public int programCounter;
        public UVSIM(string filename)
        {
            memory = new string[] { "+4010", "+0012", "+0020", "-9999", "-0020", "+9999", "-2064", "+1032", "+2020", "+2000", "+3001", "+2000", "+3001", "+0000" };
            accumulator = "-0000"; // Since this value is technically impossible it should give us errors when we are using accumulator incorrectly. Could conflict with GUI?
            programCounter = 0;
        }
        
    }
    class VM
    {
        // Controls the functions and what they do when called.
        UVSIM simulator;
        public VM(UVSIM uvsim)
        {
            simulator = uvsim;
        }
        public int ExecuteOpCode(string line)
        {
            // parses a string token for the opcode and the value as parameter, then calls it based on this.
            if (line == null)
            {
                return -1;
            }
            string opcode = line.Substring(1,2);
            if (opcode == "10" || opcode == "20" || opcode == "30" || opcode == "40") // Those opcode which have an operand.
            {
                int operand = Convert.ToInt16(line.Substring(3, 2));
                if (opcode == "10") {
                    Read(operand);
                }
                else if (opcode == "20")
                {
                    Load(operand);
                }
                else if (opcode == "30")
                {
                    Add(operand);
                }
                else if (opcode == "40")
                {
                    Branch(operand);
                }
                return 0;
            }
            if (opcode == "00")
            {
                return -1;
            }
            return -2; // Uncaught
        }
        public void Read(int toLocation)
        {
            // reads a string from STD IN and places it into memory from argument 1
            string input = Console.ReadLine();
            // Implementation would check this for proper memory writing, also this is write not read, but this is what M-1 describes. They probably wanted to read a data segment from memory. Also limitations exist for this method.
            simulator.memory[toLocation] = input;
        }
        public void Load(int fromLocation)
        {
            // loads a section of memory into accumulator
            simulator.accumulator = simulator.memory[fromLocation];
        }
        public void Add(int fromLocation)
        {
            // Because I wrote these as strings, I will now add by turning both into numbers then store accumulator as a string.
            short augend = Convert.ToInt16(simulator.memory[fromLocation]);
            short addend = Convert.ToInt16(simulator.accumulator);
            int sum = augend + addend; // int required by C#
            simulator.accumulator = sum.ToString(); // Note the function does not check for proper output, this will need to be done in a later iteration, for now I assume only proper inputs.
        }
        public void Branch(int toLocation)
        {
            // goes from our current instruction to a place in memory to start reading from there, note the program will increment after Branch, this is normal for branch statements.
            simulator.programCounter = toLocation;
        }
        public void MEMDUMP()
        {
            // Returns the internal memory
            // You can change this for GUI as it should print something.
            // return simulator.memory;
            Console.WriteLine("pc: " + simulator.programCounter.ToString());
            Console.WriteLine("Accumulator: " + simulator.accumulator.ToString());
            foreach (string s in simulator.memory)
            {
                Console.WriteLine(s);
            }
        }
    }
}
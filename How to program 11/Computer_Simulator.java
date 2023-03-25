import java.util.Scanner;

public class Computer_Simulator {
    public static final Scanner input = new Scanner(System.in);
    public static final int READ = 10;
    public static final int WRITE = 11;
    public static final int LOAD = 20;
    public static final int STORE = 21;
    public static final int ADD = 30;
    public static final int SUBTRACT = 31;
    public static final int DIVIDE = 32;
    public static final int MULTIPLY = 33;
    public static final int BRANCH = 40;
    public static final int BRANCHNEG = 41;
    public static final int BRANCHZERO = 42;
    public static final int HALT = 43;
    public static final int SENTINEL = -99999;
    public static final int MAX_MEMORY = 100;

    int[] memory = new int[MAX_MEMORY];
    int accumulator;
    int operationCode;
    int operand;
    int instructionCounter;
    int instructionRegister;

    public static void main(String[] args) {
        Computer_Simulator simpletron = new Computer_Simulator(); // 創建一個Computer_Simulator對象
        simpletron.Simpletron_Start();
        simpletron.Enter_Instructions();
        simpletron.Run_Instructions();
        simpletron.Display_Dump();
    }

    public void Simpletron_Start() {
        System.out.println("\n*** Welcome to Simpletron! ***");
        System.out.println("*** Please enter your program one instruction ***");
        System.out.println("*** (or data word) at a time. I will display ***");
        System.out.println("*** the location number and a question mark (?) ***");
        System.out.println("*** You then type the word for that location. ***");
        System.out.println("*** Type -99999 to stop entering your program.***\n");
    }

    public void Enter_Instructions() {
        int instruction = 0;
        instructionCounter = 0;
        do {
            System.out.printf("%02d ? ", instructionCounter);
            instruction = input.nextInt();
            if (instruction >= 0 && instruction < 10000) {
                memory[instructionCounter] = instruction;
                instructionCounter++;
            } else if (instruction != -99999) {
                System.out.printf("\n*** Error: invalid instruction. Please enter again. ***\n\n");
            }
        } while (instruction != SENTINEL);
    }

    public void Run_Instructions() {
        System.out.println("\n*** Program loading completed ***");
        System.out.println("*** Program execution begins ***\n");
        instructionCounter = 0;
        while (instructionRegister / 100 != HALT) {
            instructionRegister = memory[instructionCounter];
            instructionCounter++;
            operationCode = instructionRegister / 100;
            operand = instructionRegister % 100;
            switch (operationCode) {
                case READ:
                    int rec;
                    System.out.print("Enter an integer: ");
                    rec = input.nextInt();
                    if (rec < -9999 || rec > 9999) {
                        System.out.printf("\n*** Fatal Error: Register overflow. ***\n\n");
                        return;
                    }
                    memory[operand] = rec;
                    break;
                case WRITE:
                    System.out.println(memory[operand]);
                    break;
                case LOAD:
                    accumulator = memory[operand];
                    break;
                case STORE:
                    memory[operand] = accumulator;
                    break;
                case ADD:
                    accumulator += memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        System.out.printf("\n*** Fatal Error: Accumulator overflow. ***\n\n");
                        return;
                    }
                    break;
                case SUBTRACT:
                    accumulator -= memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        System.out.printf("\n*** Fatal Error: Accumulator overflow. ***\n\n");
                        return;
                    }
                    break;
                case DIVIDE:
                    if (memory[operand] == 0) {
                        System.out.printf("\n*** Fatal Error: Divide by zero. ***\n\n");
                        return;
                    }
                    accumulator /= memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        System.out.printf("\n*** Fatal Error: Accumulator overflow. ***\n\n");
                        return;
                    }
                    break;
                case MULTIPLY:
                    accumulator *= memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        System.out.printf("\n*** Fatal Error: Accumulator overflow. ***\n\n");
                        return;
                    }
                    break;
                case BRANCH:
                    instructionCounter = operand;
                    break;
                case BRANCHNEG:
                    if (accumulator < 0)
                        instructionCounter = operand;
                    break;
                case BRANCHZERO:
                    if (accumulator == 0)
                        instructionCounter = operand;
                    break;
                case HALT:
                    System.out.println("*** Simpletron execution terminated. ***");
                    break;
                default:
                    System.out.printf("\n*** Fatal Error: Invalid operation code. ***\n\n");
                    return;
            }
        }
    }

    public void Display_Dump() {
        System.out.println("\n\nREGISTERS:");
        System.out.printf("accumulator         %s%04d\n", accumulator >= 0 ? "+" : "-", Math.abs(accumulator));
        System.out.printf("instructionCounter     %02d\n", instructionCounter);
        System.out.printf("instructionRegister +%04d\n", instructionRegister);
        System.out.printf("operationCode          %02d\n", operationCode);
        System.out.printf("operand                %02d\n", operand);

        System.out.println("\nMEMORY:");
        for (int i = 0; i < 10; i++)
            System.out.printf("%6d", i);

        for (int i = 0; i < memory.length; i++) {
            if (i % 10 == 0) {
                System.out.println();
                System.out.printf("%2d ", i);
            }

            System.out.printf("%s%04d ", memory[i] >= 0 ? "+" : "-", Math.abs(memory[i]));
        }
    }

}

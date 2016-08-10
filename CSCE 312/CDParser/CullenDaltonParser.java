import java.io.*;

public class CullenDaltonParser
{
 
    private static char A_COMMAND = 0;
    private static char C_COMMAND = 1;
    private static char L_COMMAND = 2;
    private static BufferedReader br;
    private static int currentLine = 0;
    private static int currentSymbolAddress = 16;
    private static SymbolTable mysymbol;
    private static String parsestring;
    
    public CullenDaltonParser(String file)
    {
        mysymbol = new SymbolTable();
        
        mysymbol.addEntry("R0", 0);
        mysymbol.addEntry("R1", 1);
        mysymbol.addEntry("R2", 2);
        mysymbol.addEntry("R3", 3);
        mysymbol.addEntry("R4", 4);
        mysymbol.addEntry("R5", 5);
        mysymbol.addEntry("R6", 6);
        mysymbol.addEntry("R7", 7);
        mysymbol.addEntry("R8", 8);
        mysymbol.addEntry("R9", 9);
        mysymbol.addEntry("R10", 10);
        mysymbol.addEntry("R11", 11);
        mysymbol.addEntry("R12", 12);
        mysymbol.addEntry("R13", 13);
        mysymbol.addEntry("R14", 14);
        mysymbol.addEntry("R15", 15);
        mysymbol.addEntry("SCREEN", 16384);
        mysymbol.addEntry("KBD", 24576);
        
        try
        {
            br = new BufferedReader(new FileReader("testinganother.asm"));
            String line;
            FileWriter outputfile = new FileWriter("output.hack");
            
            while((line = br.readLine()) != null)
            {
                parsestring = parseNextLine();
                outputfile.write(parsestring);
            }
            
            
            
            outputfile.close();
            
            
        }
        
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        
        Entry testing = new Entry("testing", 10);

    }
    
    private String nextLine() throws IOException
    {
        String line;
        while(true)
        {
            line = br.readLine();
            if(line == null)
            {
                br.close();
                return null;
            }
            line = line.replaceAll("\\s","");
            line = line.replaceAll("//.*", "");
            return line;
        }
    }
    
    private void parseSymbols() throws IOException
    {
        String line = nextLine();
        while(line != null)
        {
            if(commandType(line) == L_COMMAND)
            {
                mysymbol.addEntry(line.substring(1,line.length()-1), currentLine);
            }
            
            else
            {
                currentLine++;
            }
        }
    }
    
    public String parseNextLine() throws Exception {
        String s = nextLine();
        while(s != null && commandType(s) == L_COMMAND)
            s = nextLine();
        if (s == null)
            return null;
        if (commandType(s) == A_COMMAND) {
            s = s.substring(1);
            if (s.charAt(0) < '0' || s.charAt(0) > '9') {
                Integer addr = (Integer) mysymbol.getAddress(s);
                if (addr == null) {
                    addr = currentSymbolAddress;
                    mysymbol.addEntry(s, addr);
                    currentSymbolAddress += 1;
                }
                return String.format("%16s", Integer.toBinaryString(addr)).replace(' ', '0');
            } else
                return String.format("%16s", Integer.toBinaryString(Integer.parseInt(s))).replace(' ', '0');
        }
        int raw = 0b1110000000000000 + (comp(s) << 6) + (dest(s) << 3) + jump(s);
        return String.format("%16s", Integer.toBinaryString(raw)).replace(' ', '0');
    }
    
    private char commandType(String command)
    {
        if (command.charAt(0) == '@')
            return A_COMMAND;
        if (command.charAt(0) == '(')
            return L_COMMAND;
        return C_COMMAND;
    }
    
    private char comp(String command) throws Exception
    {
        String s = command.replaceAll(".*=", "");
        s = s.replaceAll(";.*", "");
        switch (s) {
            case "0": return 0b0101010;
            case "1": return 0b0111111;
            case "-1": return 0b0111010;
            case "D": return 0b0001100;
            case "A": return 0b0110000;
            case "!D": return 0b0001101;
            case "!A": return 0b0110001;
            case "-D": return 0b0001111;
            case "-A": return 0b0110011;
            case "D+1": return 0b0011111;
            case "A+1": return 0b0110111;
            case "D-1": return 0b0001110;
            case "A-1": return 0b0110010;
            case "D+A": return 0b0000010;
            case "D-A": return 0b0010011;
            case "A-D": return 0b0000111;
            case "D&A": return 0b0000000;
            case "D|A": return 0b0010101;
                
            case "M": return 0b1110000;
            case "!M": return 0b1110001;
            case "-M": return 0b1110011;
            case "M+1": return 0b1110111;
            case "M-1": return 0b1110010;
            case "D+M": return 0b1000010;
            case "D-M": return 0b1010011;
            case "M-D": return 0b1000111;
            case "D&M": return 0b1000000;
            case "D|M": return 0b1010101;
            default: throw new Exception("Comparison Error!");
        }
    }
    
    private char jump(String command)
    {
        if (command.indexOf(';') == -1)
            return 0;
        String right = command.replaceAll(".*;", "");
        switch (right) {
            case "JGT": return 0b001;
            case "JEQ": return 0b010;
            case "JGE": return 0b011;
            case "JLT": return 0b100;
            case "JNE": return 0b101;
            case "JLE": return 0b110;
            case "JMP": return 0b111;
            default: return 0;
        }
    }
    
    private char dest(String command)
    {
        if (command.indexOf('=') == -1)
            return 0;
        String left = command.replaceAll("=.*", "");
        char counter = 0;
        if (left.indexOf('A') != -1)
            counter += 4;
        if (left.indexOf('D') != -1)
            counter += 2;
        if (left.indexOf('M') != -1)
            counter += 1;
        return counter;
    }
    
    public static void main(String args[])
    {
        CullenDaltonParser parsethis = new CullenDaltonParser("testinganother.asm");
    }
}

class Entry
{
    private String symbol;
    private int address;
    
    public Entry(String symbol, int address)
    {
        this.symbol = symbol;
        this.address = address;
    }
    
    public String toString()
    {
        return "(" + symbol + "," + address + ")";
    }
    
    public String getSymbol()
    {
        return symbol;
    }

    public int getAddress()
    {
        return address;
    }
}

class SymbolTable
{
    private Entry[] symbolTable;
    private int entries = 0;
    
    SymbolTable()
    {
        symbolTable = new Entry[100];
    }
    
    void addEntry(String symbol, int address)
    {
        Entry e = new Entry(symbol, address);
        symbolTable[entries] = e;
        entries++;
    }
    
    Boolean contains(String s)
    {
        for(int i = 0; i < symbolTable.length; i++){
            if(symbolTable[i].getSymbol().equals(s)){
                return true;
            }
        }
        return false;
    }
    
    int getAddress(String s)
    {
        for(int i = 0; i < symbolTable.length; i++){
            if(symbolTable[i].getSymbol().equals(s)){
                return i;
            }
        }
        return -1;
    }
    
    public String toString()
    {
        String s = "";
        for(int i = 0; i < entries; i++){
            s += symbolTable[i].getSymbol() + " " + symbolTable[i].getAddress() + "\n";
        }
        return s;
    }
}
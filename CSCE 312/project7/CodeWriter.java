import java.io.*;

public class CodeWriter
{
    private int JumpCounter;
    private PrintWriter printOut;
    
    public CodeWriter(File outFile)
    {
        try
        {
            printOut = new PrintWriter(outFile);
            JumpCounter = 0;
         }
        
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }
    
    public void fileNamer(File outFile)
    {
        // code goes here
    }
    
    public void ArithWriter(String cmd)
    {
        if(cmd.equals("add"))
        {
            printOut.print(arithTemp1() + "M=M+D\n");
        }
        
        else if(cmd.equals("sub"))
        {
            printOut.print(arithTemp1() + "M=M-D\n");
        }
        
        else if(cmd.equals("and"))
        {
            printOut.print(arithTemp1() + "M=M&D\n");
        }
        
        else if(cmd.equals("or"))
        {
            printOut.print(arithTemp1() + "M=M|D\n");
        }
        
        else if(cmd.equals("gt"))
        {
            printOut.print(arithTemp2("JLE"));
            JumpCounter++;
        }
        
        else if(cmd.equals("lt"))
        {
            printOut.print(arithTemp2("JGE"));
            JumpCounter++;
        }
        
        else if(cmd.equals("eq"))
        {
            printOut.print(arithTemp2("JNE"));
            JumpCounter++;
        }
        
        else if(cmd.equals("not"))
        {
            printOut.print("@SP\nA=M-1\nM=!M\n");
        }
        
        else if(cmd.equals("neg"))
        {
            printOut.print("D=0\n@SP\nA=M-1\nM=D-M\n");
        }
        
        else
        {
            throw new IllegalArgumentException("IllegalArgumentException");
        }
    }
    
    public void PushPop(int cmd, String seg, int index)
    {
        if(cmd == CullenDaltonParser.PUSH)
        {
            if(seg.equals("constant"))
            {
                printOut.print("@" + index + "\n" + "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
            }
            
            else if(seg.equals("local"))
            {
                printOut.print(pushT1("LCL", index, false));
            }
            
            else if(seg.equals("argument"))
            {
                printOut.print(pushT1("ARG", index, false));
            }
            
            else if(seg.equals("this"))
            {
                printOut.print(pushT1("THIS", index, false));
            }
            
            else if(seg.equals("that"))
            {
                printOut.print(pushT1("THAT", index, false));
            }
            
            else if(seg.equals("temo"))
            {
                printOut.print(pushT1("R5", index + 5, false));
            }
            
            else if(seg.equals("pointer") && index == 0)
            {
                printOut.print(pushT1("THIS", index, true));
            }
            
            else if(seg.equals("pointer") && index == 1)
            {
                printOut.print(pushT1("THAT", index, true));
            }
            
            else if(seg.equals("static"))
            {
                printOut.print(pushT1(String.valueOf(16 + index), index, true));
            }
        }
        
        else if(cmd == CullenDaltonParser.POP)
        {
            if(seg.equals("local"))
            {
                printOut.print(popT1("LCL", index, false));
            }
            
            else if(seg.equals("argument"))
            {
                printOut.print(popT1("ARG", index, false));
            }
            
            else if(seg.equals("this"))
            {
                printOut.print(popT1("THIS", index, false));
            }
            
            else if(seg.equals("that"))
            {
                printOut.print(popT1("THAT", index, false));
            }
            
            else if(seg.equals("temp"))
            {
                printOut.print(popT1("R5", index + 5, false));
            }
            
            else if(seg.equals("pointer") && index == 0)
            {
                printOut.print(popT1("THIS", index, true));
            }
            
            else if(seg.equals("pointer") && index == 1)
            {
                printOut.print(popT1("THAT", index, true));
            }
            
            else if (seg.equals("static"))
            {
                printOut.print(popT1(String.valueOf(16 + index),index,true));
            }
        }
        
        else
        {
            throw new IllegalArgumentException("IllegalArgumentException");
        }
    }
    
    public void closeFile()
    {
        printOut.close();
    }
    
    private String arithTemp1()
    {
        return "@SP\n" +
        "AM=M-1\n" +
        "D=M\n" +
        "A=A-1\n";
    }
    
    private String arithTemp2(String type)
    {
        return "@SP\n" +
        "AM=M-1\n" +
        "D=M\n" +
        "A=A-1\n" +
        "D=M-D\n" +
        "@FALSE" + JumpCounter + "\n" +
        "D;" + type + "\n" +
        "@SP\n" +
        "A=M-1\n" +
        "M=-1\n" +
        "@CONTINUE" + JumpCounter + "\n" +
        "0;JMP\n" +
        "(FALSE" + JumpCounter + ")\n" +
        "@SP\n" +
        "A=M-1\n" +
        "M=0\n" +
        "(CONTINUE" + JumpCounter + ")\n";
    }
    
    private String pushT1(String seg, int index, boolean isDirect)
    {
        String noPoint = (isDirect)? "" : "@" + index + "\n" + "A=D+A\nD=M\n";
        
        return "@" + seg + "\n" +
        "D=M\n"+
        noPoint +
        "@SP\n" +
        "A=M\n" +
        "M=D\n" +
        "@SP\n" +
        "M=M+1\n";
    }
    
    private String popT1(String seg, int index, boolean isDirect)
    {
        String noPoint = (isDirect)? "D=A\n" : "D=M\n@" + index + "\nD=D+A\n";
        
        return "@" + seg + "\n" +
        noPoint +
        "@R13\n" +
        "M=D\n" +
        "@SP\n" +
        "AM=M-1\n" +
        "D=M\n" +
        "@R13\n" +
        "A=M\n" +
        "M=D\n";
    }
    
}
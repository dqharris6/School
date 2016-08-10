// Cullen and Dalton
import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.*;

public class CodeWriter
{
    private int JumpCounter;
    private PrintWriter printOut;
    private static final Pattern labelReg = Pattern.compile("^[^0-9][0-9A-Za-z\\_\\:\\.\\$]+");
    private static String fileName = "";
    private static int labelcounter = 0;
    
    public CodeWriter(File outFile)
    {
        try
        {
            fileName = outFile.getName();
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
        fileName = outFile.getName();
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
            
            else if(seg.equals("temp"))
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
                printOut.print("@" + fileName + index + "\n" + "D=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
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
                printOut.print("@" + fileName + index + "\nD=A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n");
            }
        }
        
        else
        {
            throw new IllegalArgumentException("IllegalArgumentException");
        }
    }
    
    // -- new functions go here
    
    public void writeLabel(String label)
    {
        Matcher m = labelReg.matcher(label);
        
        if (m.find())
            printOut.print("(" + label +")\n");
        
        else
            throw new IllegalArgumentException("Wrong label format!");
    }
    
    public void writeGoto(String label)
    {
        Matcher m = labelReg.matcher(label);
        
        if (m.find())
            printOut.print("@" + label +"\n0;JMP\n");
            
        else
            throw new IllegalArgumentException("Wrong label format!");
    }
    
    public void writeIf(String label)
    {
        Matcher m = labelReg.matcher(label);
        
        if (m.find())
            printOut.print(arithTemp1() + "@" + label +"\nD;JNE\n");
            
        else
            throw new IllegalArgumentException("Wrong label format!");
        
    }

    public void writeInit()
    {
        printOut.print("@256\n" +
                         "D=A\n" +
                         "@SP\n" +
                         "M=D\n");
        writeCall("Sys.init",0);
    }

    public void writeCall(String functionName, int numArgs)
    {
        String newLabel = "RETURN_LABEL" + (labelcounter++);
        
        printOut.print("@" + newLabel + "\n" + "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");//push return address
        printOut.print(pushT1("LCL",0,true));//push LCL
        printOut.print(pushT1("ARG",0,true));//push ARG
        printOut.print(pushT1("THIS",0,true));//push THIS
        printOut.print(pushT1("THAT",0,true));//push THAT
        
        printOut.print("@SP\n" +
                         "D=M\n" +
                         "@5\n" +
                         "D=D-A\n" +
                         "@" + numArgs + "\n" +
                         "D=D-A\n" +
                         "@ARG\n" +
                         "M=D\n" +
                         "@SP\n" +
                         "D=M\n" +
                         "@LCL\n" +
                         "M=D\n" +
                         "@" + functionName + "\n" +
                         "0;JMP\n" +
                         "(" + newLabel + ")\n"
                         );
        
    }
    
    public void writeReturn()
    {
        printOut.print(returnTemplate());
    }
    
    public void writeFunction(String functionName, int numLocals)
    {
        printOut.print("(" + functionName +")\n");
        
        for (int i = 0; i < numLocals; i++)
        {
            PushPop(CullenDaltonParser.PUSH,"constant",0);
        }
    }
    
    public String preFrameTemplate(String position)
    {
        return "@R11\n" +
        "D=M-1\n" +
        "AM=D\n" +
        "D=M\n" +
        "@" + position + "\n" +
        "M=D\n";
        
    }
    
    public String returnTemplate(){
        
        return "@LCL\n" +
        "D=M\n" +
        "@R11\n" +
        "M=D\n" +
        "@5\n" +
        "A=D-A\n" +
        "D=M\n" +
        "@R12\n" +
        "M=D\n" +
        popT1("ARG",0,false) +
        "@ARG\n" +
        "D=M\n" +
        "@SP\n" +
        "M=D+1\n" +
        preFrameTemplate("THAT") +
        preFrameTemplate("THIS") +
        preFrameTemplate("ARG") +
        preFrameTemplate("LCL") +
        "@R12\n" +
        "A=M\n" +
        "0;JMP\n";
    }
    
    // -- new functions go here
    
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
// CullenDaltonCompilerII

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CodeWriter
{
    private int JumpCounter;
    private PrintWriter StreamOut;
    private static final Pattern regexPattern = Pattern.compile("^[^0-9][0-9A-Za-z\\_\\:\\.\\$]+");
    private static int labelcounter = 0;
    private static String fileName = "";

    public CodeWriter(File fileOut)
    {
        try
        {
            fileName = fileOut.getName();
            StreamOut = new PrintWriter(fileOut);
            JumpCounter = 0;
        }
        
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }
    
    public void filenamer(File fileOut)
    {
        fileName = fileOut.getName();
    }
    
    public void writeArithmetic(String command)
    {
        
        if (command.equals("add"))
        {
            StreamOut.print(arithmeticTemplate1() + "M=M+D\n");
        }
        
        else if (command.equals("sub"))
        {
            StreamOut.print(arithmeticTemplate1() + "M=M-D\n");
        }
        
        else if (command.equals("and"))
        {
            StreamOut.print(arithmeticTemplate1() + "M=M&D\n");
        }
        
        else if (command.equals("or"))
        {
            StreamOut.print(arithmeticTemplate1() + "M=M|D\n");
        }
        
        else if (command.equals("gt"))
        {
            StreamOut.print(arithmeticTemplate2("JLE"));
            JumpCounter++;
        }
        
        else if (command.equals("lt"))
        {
            StreamOut.print(arithmeticTemplate2("JGE"));
            JumpCounter++;
        }
        
        else if (command.equals("eq"))
        {
            StreamOut.print(arithmeticTemplate2("JNE"));
            JumpCounter++;
        }
        
        else if (command.equals("not"))
        {
            StreamOut.print("@SP\nA=M-1\nM=!M\n");
        }
        
        else if (command.equals("neg"))
        {
            StreamOut.print("D=0\n@SP\nA=M-1\nM=D-M\n");
        }
        
        else
        {
            throw new IllegalArgumentException("Call writeArithmetic() for a non-arithmetic command");
        }
    }
    
    public void writePushPop(int command, String segment, int index)
    {
        
        if (command == CullenDaltonParser.PUSH)
        {
            if (segment.equals("constant")){
                
                StreamOut.print("@" + index + "\n" + "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
            }
            
            else if (segment.equals("local"))
            {
                StreamOut.print(pushTemplate1("LCL",index,false));
            }
            
            else if (segment.equals("argument"))
            {
                StreamOut.print(pushTemplate1("ARG",index,false));
            }
            
            else if (segment.equals("this"))
            {
                StreamOut.print(pushTemplate1("THIS",index,false));
            }
            
            else if (segment.equals("that"))
            {
                StreamOut.print(pushTemplate1("THAT",index,false));
            }
            
            else if (segment.equals("temp"))
            {
                StreamOut.print(pushTemplate1("R5", index + 5,false));
            }
            
            else if (segment.equals("pointer") && index == 0)
            {
                StreamOut.print(pushTemplate1("THIS",index,true));
            }
            
            else if (segment.equals("pointer") && index == 1)
            {
                StreamOut.print(pushTemplate1("THAT",index,true));
            }
            
            else if (segment.equals("static"))
            {
                StreamOut.print("@" + fileName + index + "\n" + "D=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
            }
        }
        
        else if(command == CullenDaltonParser.POP)
        {
            if (segment.equals("local"))
            {
                StreamOut.print(popTemplate1("LCL",index,false));
            }
            
            else if (segment.equals("argument"))
            {
                StreamOut.print(popTemplate1("ARG",index,false));
            }
            
            else if (segment.equals("this"))
            {
                StreamOut.print(popTemplate1("THIS",index,false));
            }
            
            else if (segment.equals("that"))
            {
                StreamOut.print(popTemplate1("THAT",index,false));
            }
            
            else if (segment.equals("temp"))
            {
                StreamOut.print(popTemplate1("R5", index + 5,false));
            }
            
            else if (segment.equals("pointer") && index == 0)
            {
                StreamOut.print(popTemplate1("THIS",index,true));
            }
            
            else if (segment.equals("pointer") && index == 1)
            {
                StreamOut.print(popTemplate1("THAT",index,true));
            }
            
            else if (segment.equals("static"))
            {
                StreamOut.print("@" + fileName + index + "\nD=A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n");
            }
        }
        
        else
        {
            throw new IllegalArgumentException("Call writePushPop() for a non-pushpop command");
        }
    }
    
    public void writeLabel(String label)
    {
        Matcher m = regexPattern.matcher(label);
        
        if (m.find())
        {
            StreamOut.print("(" + label +")\n");
        }
        
        else
        {
            throw new IllegalArgumentException("Wrong label format!");
        }
    }
    
    public void writeGoto(String label)
    {
        Matcher m = regexPattern.matcher(label);
        
        if (m.find())
        {
            StreamOut.print("@" + label +"\n0;JMP\n");
        }
        
        else
        {
            throw new IllegalArgumentException("Wrong label format!");
        }
    }

    public void writeIf(String label)
    {
        Matcher m = regexPattern.matcher(label);
        
        if (m.find())
        {
            StreamOut.print(arithmeticTemplate1() + "@" + label +"\nD;JNE\n");
        }
        
        else
        {
            throw new IllegalArgumentException("Wrong label format!");
        }
    }
    
    public void writeInit()
    {
        StreamOut.print("@256\n" +
                         "D=A\n" +
                         "@SP\n" +
                         "M=D\n");
        writeCall("Sys.init",0);
    }
 
    public void writeCall(String functionName, int numArgs)
    {
        String newLabel = "RETURN_LABEL" + (labelcounter++);
        
        StreamOut.print("@" + newLabel + "\n" + "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
        StreamOut.print(pushTemplate1("LCL",0,true));
        StreamOut.print(pushTemplate1("ARG",0,true));
        StreamOut.print(pushTemplate1("THIS",0,true));
        StreamOut.print(pushTemplate1("THAT",0,true));
        
        StreamOut.print("@SP\n" +
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
        StreamOut.print(returnTemplate());
    }
    
    public void writeFunction(String functionName, int numLocals)
    {
        StreamOut.print("(" + functionName +")\n");
        
        for (int i = 0; i < numLocals; i++)
        {
            writePushPop(CullenDaltonParser.PUSH,"constant",0);
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

    public String returnTemplate()
    {
        return "@LCL\n" +
        "D=M\n" +
        "@R11\n" +
        "M=D\n" +
        "@5\n" +
        "A=D-A\n" +
        "D=M\n" +
        "@R12\n" +
        "M=D\n" +
        popTemplate1("ARG",0,false) +
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
    
    public void close()
    {
        StreamOut.close();
    }

    private String arithmeticTemplate1()
    {
        return "@SP\n" +
        "AM=M-1\n" +
        "D=M\n" +
        "A=A-1\n";
    }
    
    private String arithmeticTemplate2(String type)
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
    
    private String pushTemplate1(String segment, int index, boolean isDirect)
    {
        String noPointerCode = (isDirect)? "" : "@" + index + "\n" + "A=D+A\nD=M\n";
        
        return "@" + segment + "\n" +
        "D=M\n"+
        noPointerCode +
        "@SP\n" +
        "A=M\n" +
        "M=D\n" +
        "@SP\n" +
        "M=M+1\n";
    }
    
    private String popTemplate1(String segment, int index, boolean isDirect)
    {
        String noPointerCode = (isDirect)? "D=A\n" : "D=M\n@" + index + "\nD=D+A\n";
        
        return "@" + segment + "\n" +
        noPointerCode +
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
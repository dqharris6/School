// CullenDaltonCompilerII

import java.io.*;
import java.util.*;

public class VMtranslator
{

    public static ArrayList<File> getVMFiles(File dir)
    {
        File[] files = dir.listFiles();
        
        ArrayList<File> result = new ArrayList<File>();
        
        for (File f:files)
        {
            
            if (f.getName().endsWith(".vm"))
            {
                result.add(f);
            }
        }
        
        return result;
        
    }
    
    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.out.println("Usage:java VMtranslator [filename|directory]");
        }
        
        else
        {
            
            String fileInName = args[0];
            
            File fileIn = new File(fileInName);
            
            String fileOutPath = "";
            
            File fileOut;
            
            CodeWriter writer;
            
            ArrayList<File> vmFiles = new ArrayList<File>();
            
            if (fileIn.isFile())
            {
                String path = fileIn.getAbsolutePath();
                
                if (!CullenDaltonParser.getExt(path).equals(".vm"))
                {
                    throw new IllegalArgumentException(".vm file is required!");
                }
                
                vmFiles.add(fileIn);
                
                fileOutPath = fileIn.getAbsolutePath().substring(0, fileIn.getAbsolutePath().lastIndexOf(".")) + ".asm";
            }
            
            else if (fileIn.isDirectory())
            {
                vmFiles = getVMFiles(fileIn);
                
                if (vmFiles.size() == 0)
                {
                    throw new IllegalArgumentException("No vm file in this directory");
                }
                
                fileOutPath = fileIn.getAbsolutePath() + "/" +  fileIn.getName() + ".asm";
            }
            
            fileOut = new File(fileOutPath);
            writer = new CodeWriter(fileOut);
            
            writer.writeInit();
            
            for (File f : vmFiles)
            {
                writer.filenamer(f);
                
                CullenDaltonParser CullenDaltonParser = new CullenDaltonParser(f);
                
                int type = -1;
                
                while (CullenDaltonParser.hasMoreCommands())
                {
                    CullenDaltonParser.advance();
                    
                    type = CullenDaltonParser.commandType();
                    
                    if (type == CullenDaltonParser.ARITHMETIC)
                    {
                        writer.writeArithmetic(CullenDaltonParser.arg1());
                    }
                    
                    else if (type == CullenDaltonParser.POP || type == CullenDaltonParser.PUSH)
                    {
                        writer.writePushPop(type, CullenDaltonParser.arg1(), CullenDaltonParser.arg2());
                    }
                    
                    else if (type == CullenDaltonParser.LABEL)
                    {
                        writer.writeLabel(CullenDaltonParser.arg1());
                    }
                    
                    else if (type == CullenDaltonParser.GOTO)
                    {
                        writer.writeGoto(CullenDaltonParser.arg1());
                    }
                    
                    else if (type == CullenDaltonParser.IF)
                    {
                        writer.writeIf(CullenDaltonParser.arg1());
                    }
                    
                    else if (type == CullenDaltonParser.RETURN)
                    {
                        writer.writeReturn();
                    }
                    
                    else if (type == CullenDaltonParser.FUNCTION)
                    {
                        writer.writeFunction(CullenDaltonParser.arg1(),CullenDaltonParser.arg2());
                    }
                    
                    else if (type == CullenDaltonParser.CALL)
                    {
                        writer.writeCall(CullenDaltonParser.arg1(),CullenDaltonParser.arg2());
                    }
                }
            }

            writer.close();
            
            System.out.println("File created : " + fileOutPath);
        }
    }
}
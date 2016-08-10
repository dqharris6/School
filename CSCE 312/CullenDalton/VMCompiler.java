import java.io.*;
import java.util.*;

public class VMCompiler
{
    public static ArrayList<File> getFiles(File dir)
    {
        File[] files = dir.listFiles();
        ArrayList<File> result = new ArrayList<File>();
        for (File f:files)
        {
            if(f.getName().endsWith(".vm"))
            {
                result.add(f);
            }
        }
        
        return result;
    }
    
    public static void main(String[] args)
    {
        if(args.length != 1)
        {
            System.out.println("Java VMCompiler [filename | directory]");
        }
        
        else
        {
            File inFile = new File(args[0]);
            String outFilePath = "";
            File outFile;
            CodeWriter writer;
            ArrayList<File> myVMFiles = new ArrayList<File>();
            
            if(inFile.isFile())
            {
                String path = inFile.getAbsolutePath();
                
                if(!CullenDaltonParser.getExtension(path).equals(".vm"))
                {
                    throw new IllegalArgumentException("No files found.");
                }
                
                myVMFiles.add(inFile);
                
                outFilePath = inFile.getAbsolutePath().substring(0,inFile.getAbsolutePath().lastIndexOf(".")) + ".asm";
            }
            
            else if(inFile.isDirectory())
            {
                myVMFiles = getFiles(inFile);
                
                if(myVMFiles.size() == 0)
                {
                    throw new IllegalArgumentException("No files found.");
                }
                
                outFilePath = inFile.getAbsolutePath() + "/" + inFile.getName() + ".asm";
            }
            
            outFile = new File(outFilePath);
            writer = new CodeWriter(outFile);
            
            writer.writeInit();
            
            for (File f: myVMFiles)
            {
                CullenDaltonParser cullendaltonparser = new CullenDaltonParser(f);
                writer.fileNamer(f);
                int type = -1;
                
                while(cullendaltonparser.moreCommands())
                {
                    cullendaltonparser.iterate();
                    type = cullendaltonparser.commandType();
                    
                    if(type == CullenDaltonParser.ARITHMETIC)
                    {
                        writer.ArithWriter(cullendaltonparser.argumentOne());
                    }
                    
                    else if(type == CullenDaltonParser.POP || type == CullenDaltonParser.PUSH)
                    {
                        writer.PushPop(type, cullendaltonparser.argumentOne(), cullendaltonparser.argumentTwo());
                    }
                }
            }
            
            writer.closeFile();
            
            System.out.println("File created : " + outFilePath);
        }
    }
}
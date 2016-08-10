import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Scanner;
import java.util.IllegalFormatException;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.io.File;

public class CullenDaltonParser
{
	private Scanner commands;
	public static ArrayList<String> myCommands = new ArrayList<String>();
	private String current;

	public static final int ARITHMETIC = 0;
	public static final int PUSH = 1;
	public static final int POP = 2;
	public static final int LABEL = 3;
	public static final int GOTO = 4;
	public static final int IF = 5;
	public static final int FUNCTION = 6;
	public static final int RETURN = 7;
	public static final int CALL = 8;

	private int argumentType;
	private String argument1;
	private int argument2; 

	
	static
	{
		myCommands.add("add");
		myCommands.add("sub");
		myCommands.add("neg");
		myCommands.add("eq");
		myCommands.add("gt");
		myCommands.add("lt");
		myCommands.add("and");
		myCommands.add("or");
		myCommands.add("not");
	}

 


	public CullenDaltonParser(File filename)
	{
		argumentType = -1;
		argument1 = "";
		argument2 = -1;

		try{
			commands = new Scanner(filename);

			String initialProcessing = "";
			String line = "";

			while(commands.hasNext())
			{
				line = removeComments(commands.nextLine().trim());

				if(line.length() > 0)
					initialProcessing += line + "\n";

			}

			commands = new Scanner(initialProcessing);
		}
		catch(FileNotFoundException e)
		{
			System.out.println("couldn't find file");
		}

	}

	public boolean moreCommands()
	{
		return commands.hasNextLine();
	}

	public void iterate()
	{
		current = commands.nextLine();
		argument1 = "";
		argument2 = -1;

		String[] arrayOfStrings = current.split(" ");

		if(arrayOfStrings.length > 3)
            throw new IllegalArgumentException("too many arguments, invalid");

		if(myCommands.contains(arrayOfStrings[0]))
		{
			argumentType = ARITHMETIC;
			argument1 = arrayOfStrings[0];
		}
		else if(arrayOfStrings[0].equals("return"))
		{
			argumentType = RETURN;
			argument1 = arrayOfStrings[0];
		}
		else
		{
			argument1 = arrayOfStrings[1];

			if(arrayOfStrings[0].equals("push"))
			{
				argumentType = PUSH;
			}
			else if(arrayOfStrings[0].equals("pop"))
			{
				argumentType = POP;
			}
			else if(arrayOfStrings[0].equals("label"))
			{
				argumentType = LABEL;
			}
			else if(arrayOfStrings[0].equals("if-goto"))
			{
				argumentType = IF;
			}
			else if(arrayOfStrings[0].equals("goto"))
			{
				argumentType = GOTO;
			}
			else if(arrayOfStrings[0].equals("function"))
			{
				argumentType = FUNCTION;
			}
			else if(arrayOfStrings[0].equals("call"))
			{
				argumentType = CALL;
			}	
			else
			{
				throw new IllegalArgumentException("unknown command");
			}

			if(argumentType == PUSH || argumentType == POP || argumentType == FUNCTION || argumentType == CALL)
			{
				try
				{
					argument2 = Integer.parseInt(arrayOfStrings[2]);
				}
				catch(Exception e)
				{
					throw new IllegalArgumentException("2nd argument is not integer");
				}
			}
		}
	}

	public int commandType()
	{
		if(argumentType != -1)
		{
			return argumentType;
		}
		else
		{
			throw new IllegalStateException("No command input");
		}
	}

	public String argumentOne()
	{
		if(commandType() != RETURN)
			return argument1;
		else
			throw new IllegalStateException("illegal argument 1");
	}

	public int argumentTwo()
	{
		if(commandType() == PUSH || commandType() == POP || commandType() == FUNCTION || commandType() == CALL)
		{
			return argument2;
		}
		else
		{
			throw new IllegalStateException("illegal argument 2");
		}
	}

	public static String removeComments(String input)
	{
		int position = input.indexOf("//");

		if(position != -1)
			input = input.substring(0, position);

		return input;
	}

	public static String removeWhiteSpace(String input)
	{
		String output = "";

		if(input.length() != 0)
		{
			String[] arrayOfStrings = input.split(" ");

			for(String s : arrayOfStrings)
			{
				output += s;
			}
		}

		return output;
	}

	public static String getExtension(String filename)
	{
		int index = filename.indexOf('.');

		String output = filename.substring(index);

		return output;
	}
}


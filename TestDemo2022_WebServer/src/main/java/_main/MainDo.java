package _main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.ws.rs.GET;
import javax.ws.rs.Path;


@Path("/led04")
public class MainDo implements MainDo_func
{
	private interface command
	{
//		static String test               = "echo test";
		static String pigs_pin04_init    = "pigs m  4 w";
		static String pigs_pin04_check   = "pigs mg 4  ";
		static String pigs_pin04_read    = "pigs r 4   ";
		static String pigs_pin04_write_0 = "pigs w 4 0 ";
		static String pigs_pin04_write_1 = "pigs w 4 1 ";		
	}	

	static
	{
		try
		{
			Runtime.getRuntime().exec(command.pigs_pin04_init).waitFor();
		} catch (IOException | InterruptedException e)
		{
			e.printStackTrace();
		}
	}

	@GET
	@Path("/check")
	public String check() throws IOException, InterruptedException
	{
		Process process = Runtime.getRuntime().exec(command.pigs_pin04_check);
		process.waitFor();
		return String.format("out1:\n%s\nout2:\n%s\n", MainDo_func.readTextInStream(process.getInputStream()), MainDo_func.readTextInStream(process.getErrorStream()));
	}
	
	@GET
	@Path("")
	public String read() throws IOException, InterruptedException
	{
		Process process = Runtime.getRuntime().exec(command.pigs_pin04_read);

		String text_return;
		if(process.waitFor() == 0)
		{
			text_return = MainDo_func.readTextInStream(process.getInputStream());
		} else 
		{
			text_return = "X";
		}
		return text_return;
	}
	
	@GET
	@Path("/on")
	public String write_1() throws IOException, InterruptedException
	{
		Process process = Runtime.getRuntime().exec(command.pigs_pin04_write_1);
		process.waitFor();
		return this.read();
	}

	@GET
	@Path("/off")
	public String write_0() throws IOException, InterruptedException
	{
		Process process = Runtime.getRuntime().exec(command.pigs_pin04_write_0);
		process.waitFor();
		return this.read();
	}
}

interface MainDo_func
{
	static String readTextInStream(InputStream stream) throws IOException
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(stream));

		String temp;
		StringBuffer buffer = new StringBuffer();
		while( (temp=reader.readLine())!=null )
		{
			buffer.append(temp);
		}
		return buffer.substring(0);
	}
}



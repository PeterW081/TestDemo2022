package ctrl.restful;

import java.io.IOException;

import javax.ws.rs.GET;
import javax.ws.rs.Path;

import function.gpio.GPIO_Define;
import function.gpio.GPIO_Func_Led;


@Path("/led04")
public class Led implements GPIO_Define
{
	static private Pin pin_led = Pin.PIN04;
	static
	{
		GPIO_Func_Led.enable(pin_led);
	}

	@GET
	@Path("")
	public String read() throws IOException, InterruptedException
	{
		return String.valueOf(GPIO_Func_Led.status(pin_led));
	}
	
	@GET
	@Path("/on")
	public String write_on() throws IOException, InterruptedException
	{
		GPIO_Func_Led.set_on(pin_led);
		return this.read();
	}

	@GET
	@Path("/off")
	public String write_off() throws IOException, InterruptedException
	{
		GPIO_Func_Led.set_off(pin_led);
		return this.read();
	}
}


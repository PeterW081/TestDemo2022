package ctrl.main;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.glassfish.jersey.servlet.ServletContainer;

import function.gpio.GPIO_Core;

interface Config
{
	int port = 8080;
	String pathLibJniGpio = "/opt/TestDemo2022/libJniGpio.so";
	String parameterJerseyPackages[] = { "ctrl.restful", };
	String pathSpec = "/*";
}
public class Main implements Config
{
	public static void main(String[] args) throws Exception
	{
		StringBuffer parameterJerseyPackages = new StringBuffer();
		for(String var: Main.parameterJerseyPackages)
		{
			parameterJerseyPackages.append(var).append(";");
		}
		///
		GPIO_Core.force_load();
		///
		ServletContextHandler handler = new ServletContextHandler(ServletContextHandler.NO_SESSIONS);
		handler.setContextPath("/");
		ServletHolder holder = handler.addServlet(ServletContainer.class, pathSpec);
		holder.setInitParameter("jersey.config.server.provider.packages", parameterJerseyPackages.toString());
		Server server = new Server(port);		
		server.setHandler(handler);		
		server.start();
		System.out.println("listen... " + port);
		server.join();
	}
}

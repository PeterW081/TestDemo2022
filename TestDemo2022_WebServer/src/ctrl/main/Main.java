package ctrl.main;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.glassfish.jersey.servlet.ServletContainer;

interface Config
{
	int port = 8080;
	String pathLibJniGpio = "/var/lib/tomcat9/webapps/libJniGpio.so";
	String parameterJerseyPackages[] = { "ctrl.restful", };
	String pathSpec = "/*";	// "/rest/*"
}
public class Main implements Config
{
	public static void main(String[] args) throws Exception
	{
		System.out.println("ver: " + "1660064530");
		StringBuffer parameterJerseyPackages = new StringBuffer();
		for(String var: Main.parameterJerseyPackages)
		{
			parameterJerseyPackages.append(var).append(";");
		}
		///
		ServletContextHandler ctx = new ServletContextHandler(ServletContextHandler.NO_SESSIONS);
		ctx.setContextPath("/");
		ServletHolder serHol = ctx.addServlet(ServletContainer.class, pathSpec);
		serHol.setInitParameter("jersey.config.server.provider.packages", parameterJerseyPackages.toString());
		Server server = new Server(port);		
		server.setHandler(ctx);		
		server.start();
		System.out.println("listen... " + port);
		server.join();
	}
}

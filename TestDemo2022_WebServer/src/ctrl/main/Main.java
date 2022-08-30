package ctrl.main;

import java.util.HashSet;
import java.util.Set;

import javax.servlet.ServletContext;
import javax.websocket.DeploymentException;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.websocket.jsr356.server.ServerContainer;
import org.eclipse.jetty.websocket.jsr356.server.deploy.WebSocketServerContainerInitializer;
import org.glassfish.jersey.servlet.ServletContainer;
import org.reflections.Reflections;

import function.gpio.GPIO_Core;

interface Config
{
	int port = 8080;
	String jni_pathLibGpio = "/opt/TestDemo2022/libJniGpio.so";
	String resetful_pathSpec = "/*";
	String resetful_JerseyPackages[] = { "ctrl.restful", };
	String websocket_JavaxPackages[] = { "ctrl.websocket", };
}

public class Main implements Config
{
	public static void main(String[] args) throws Exception
	{
		GPIO_Core.force_load();
		///
		ServletContextHandler handler = new ServletContextHandler();
		handler.setContextPath("/");
		StringBuffer parameterJerseyPackages = new StringBuffer();
		for (String var : Main.resetful_JerseyPackages)
		{
			parameterJerseyPackages.append(var).append(";");
		}
		ServletHolder holder = new ServletHolder(ServletContainer.class);
		holder.setInitParameter("jersey.config.server.provider.packages", parameterJerseyPackages.toString());
		handler.addServlet(holder, Main.resetful_pathSpec);
		Set<Class<?>> itcsServerEndpointClasses = new HashSet<Class<?>>();
		for (String var : Main.websocket_JavaxPackages)
		{
			Reflections reflections = new Reflections(var);
			itcsServerEndpointClasses.addAll(reflections.getTypesAnnotatedWith(javax.websocket.server.ServerEndpoint.class));
		}
		WebSocketServerContainerInitializer.Configurator configurator = new WebSocketServerContainerInitializer.Configurator()
		{
			public void accept(ServletContext servletContext, ServerContainer serverContainer) throws DeploymentException
			{
				for (Class<?> var : itcsServerEndpointClasses)
				{
					serverContainer.addEndpoint(var);
				}
			}
		};
		WebSocketServerContainerInitializer.configure(handler, configurator);
		///
		Server server = new Server(port);
		server.setHandler(handler);
		server.start();
		System.out.println("listen... " + port);
		server.join();
	}
}

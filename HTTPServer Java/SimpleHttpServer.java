
import java.util.*;
import java.io.IOException;
import java.net.*;






public class SimpleHttpServer {

    public static final int port= 8080;
    public static final String Document_dir = "./www";


    public static void main(String[] args) throws IOException{

        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Listening to connection on Port #: "+port);

        while(true){

            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected: "+clientSocket.getRemoteSocketAddress());

            // we will handle the client request in a seperate thread for concurrency.

            new Thread(() -> handleClientRequest(clientSocket)).start();


        }

    }


     /*
      *  Handles the client connection to the server Socket.
      */
    
    private static void handleClientRequest(Socket clientSocket){





    }
    
}

package communication;

import main.Utils;
import storage.DataRepository;
import storage.SensorData;

import java.util.Observable;
import java.util.Observer;

public class ServerCommunicationController implements Observer {

    @Override
    public void update(Observable o, Object arg) {
        System.out.println("[SERVER COMMUNICATION CONTROLLER]");
//        System.out.println(arg.toString());
        ServerMessage serverMessage = new ServerMessage(((SensorData) arg).getStepsCount(), Utils.getClientId(), ((SensorData) arg).getTimestamp());
        System.out.println(serverMessage.toString());
    }
}

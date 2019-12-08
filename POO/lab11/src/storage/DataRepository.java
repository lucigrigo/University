package storage;


import java.util.LinkedList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

/**
 * Persists sensor data. Observable, its observers are notified when data is added it to.
 */
public class DataRepository extends Observable { // TODO make this an Observable

    private static List<SensorData> data = new LinkedList<>();

    public void addData(SensorData dataRecord) {
        // TODO
        // store data (e.g. in a List)
        // notifiy observers
        data.add(dataRecord);
        super.setChanged();
        super.notifyObservers(dataRecord);
    }

    // TODO implement a method to get the stored data (needed by the strategies)
    public static List<SensorData> getData() {
        return data;
    }
}



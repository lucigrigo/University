package dataprocessing;

import main.MainApp;
import storage.DataRepository;
import storage.SensorData;

import java.util.concurrent.TimeUnit;

public class FilteredStepCountStrategy implements StepCountStrategy {

    private static final int MAX_DIFF_STEPS_CONSECUTIVE_RECORDS = 1000;
    private static final long TIME_FOR_MAX_DIFF = TimeUnit.SECONDS.toMillis(1);

    @Override
    public int getTotalSteps() {
        int count = 0;
        long previousTS = 0;
        for (SensorData data : DataRepository.getData()) {
            long timePeriod = data.getTimestamp() - previousTS;
            if (data.getStepsCount() >= 0
                    && data.getStepsCount() <= 1000 * timePeriod) {
                count += data.getStepsCount();
            }
            previousTS = data.getTimestamp();
        }

        return count;
    }

    @Override
    public String getStrategyDescription() {
        return "Filtered Step Count Strategy";
    }
}

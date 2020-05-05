package dataprocessing;

import main.Utils;

public class StepCountStrategyFactory {

    public static StepCountStrategy createStrategy(String type) {
        switch (type) {
            case Utils.BASIC_STRATEGY:
                return new BasicStepCountStrategy();
            case Utils.FILTERED_STRATEGY:
                return new FilteredStepCountStrategy();
            default:
                return null;
        }
    }
}

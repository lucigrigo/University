package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public class ConsoleLogger extends LoggerBase {

    public ConsoleLogger(EnumSet<LogLevel> enumSet) {
        super(enumSet);
    }

    @Override
    public void writeMessage(String message) {
//        System.out.println("[Console] " + LogLevel.all());
        System.out.println("[Console] " + message);
    }
}

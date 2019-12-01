package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public class EmailLogger extends LoggerBase {

    public EmailLogger(EnumSet<LogLevel> enumSet) {
        super(enumSet);
    }

    @Override
    public void writeMessage(String message) {
        System.out.println("[Email] " + message);
    }
}

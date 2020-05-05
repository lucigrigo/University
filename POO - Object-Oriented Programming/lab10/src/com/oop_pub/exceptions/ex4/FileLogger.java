package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public class FileLogger extends LoggerBase {

    public FileLogger(EnumSet<LogLevel> enumSet) {
        super(enumSet);
    }

    @Override
    public void writeMessage(String message) {
        System.out.println("[File] " + message);
    }
}

package com.company;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.Pipe;
import java.nio.channels.Pipe.SinkChannel;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        try {
            Pipe pipe = Pipe.open();

            Runnable writer = new Runnable() {
                @Override
                public void run() {
                    try {
                        Pipe.SinkChannel sinkChannel = pipe.sink();
                        ByteBuffer buffer = ByteBuffer.allocate(56);

                        for (int i = 0; i < 10; i++) {
                            String currentTime = "The time is: " + System.currentTimeMillis();

                            buffer.put(currentTime.getBytes());
                            buffer.flip();

                            while (buffer.hasRemaining()) {
                                sinkChannel.write(buffer);
                            }
                            buffer.flip();
                            Thread.sleep(100);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            };

            Runnable reader = new Runnable() {
                @Override
                public void run() {
                    try {
                        Pipe.SourceChannel sourceChannel = pipe.source();
                        ByteBuffer buffer = ByteBuffer.allocate(56);

                        for (int i = 0; i < 10; i++) {
                            int bytesRead = sourceChannel.read(buffer);
                            byte[] timeString = new byte[bytesRead];
                            buffer.flip();
                            buffer.get(timeString);
                            System.out.println("Reader Thread " + new String(timeString));
                            buffer.flip();
                            Thread.sleep(100);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            };

            new Thread(writer).start();
            new Thread(reader).start();

        } catch (IOException ioe) {
            ioe.printStackTrace();
        }

        /*
//        try {
////            FileInputStream file = new FileInputStream("data.txt");
////            FileChannel channel = file.getChannel();
//            Path dataPath = FileSystems.getDefault().getPath("data.txt");
////            standard open option is CREATE or TRUNKATE_EXISTING
//            Files.write(dataPath, "\nLine 4".getBytes("UTF-8"), StandardOpenOption.APPEND);
////            for very large files is not recommended
////            readAllLines() method reads all the lines into memory !
//            List<String> lines = Files.readAllLines(dataPath);
//            for (String line : lines) {
//                System.out.println(line);
//            }
//
//        } catch (IOException ioe) {
//            ioe.printStackTrace();
//        }

        try (FileOutputStream binFile = new FileOutputStream("data.dat");
             FileChannel binChannel = binFile.getChannel()) {

            //  WRITING
            byte[] outputBytes = "Hello World!".getBytes();
//            byte[] outputBytes2 = "Nice to meet you!".getBytes();

//            ByteBuffer buffer = ByteBuffer.allocate(100);
//            buffer.put(outputBytes).putInt(245).putInt(-9876543).put(outputBytes2).putInt(1000);
//            buffer.flip();

            ByteBuffer buffer = ByteBuffer.allocate(100);
            buffer.put(outputBytes);
            long int1Pos = outputBytes.length;
            buffer.putInt(245);
            long int2Pos = int1Pos + Integer.BYTES;
            buffer.putInt(-9876543);
            byte[] outputBytes2 = "Nice to meet you!".getBytes();
            buffer.put(outputBytes2);
            long int3Pos = int2Pos + Integer.BYTES + outputBytes2.length;
            buffer.putInt(1000);
            buffer.flip();

            binChannel.write(buffer);

            RandomAccessFile raf = new RandomAccessFile("data.dat", "rwd");
            FileChannel channel = raf.getChannel();

            ByteBuffer readBuffer = ByteBuffer.allocate(100);
            channel.read(readBuffer);
            readBuffer.flip();
            byte[] inputString = new byte[outputBytes.length];
            readBuffer.get(inputString);
            System.out.println("input string = " + new String(inputString));
            readBuffer.position((int) int3Pos);
            System.out.println("int1 = " + readBuffer.getInt());
            readBuffer.position((int) int2Pos);
            System.out.println("int2 = " + readBuffer.getInt());
            byte[] inputString2 = new byte[outputBytes2.length];
            readBuffer.get(inputString2);
            System.out.println("input string 2 = " + new String(inputString2));
            readBuffer.position((int) int1Pos);
            System.out.println("int3 = " + readBuffer.getInt());

            RandomAccessFile copyFile = new RandomAccessFile("data_copy.dat", "rwd");
            FileChannel copyChannel = copyFile.getChannel();
            channel.position(0);
//            long numTransferred = copyChannel.transferFrom(channel, 0, channel.size());
            long numTransferred = channel.transferTo(0, channel.size(), copyChannel);
            System.out.println("numTransferred  = " + numTransferred);

            channel.close();
            raf.close();
            copyChannel.close();
            copyFile.close();


//            ByteBuffer buffer = ByteBuffer.allocate(outputBytes.length);
//            buffer.put(outputBytes);
//
//            buffer.flip();
//            int numBytes = binChannel.write(buffer);
//            System.out.println("number of string bytes : " + numBytes);
//
//            ByteBuffer intBuffer = ByteBuffer.allocate(Integer.BYTES);
//            intBuffer.putInt(245);
//            intBuffer.flip();
//            numBytes = binChannel.write(intBuffer);
//            System.out.println("number of int bytes : " + numBytes);
//
//            intBuffer.flip();
//            intBuffer.putInt(-98765);
//            intBuffer.flip();
//            numBytes = binChannel.write(intBuffer);
//            System.out.println("number of negative int bytes : " + numBytes + "\n\n\n\n");

            // READING
//            RandomAccessFile raf = new RandomAccessFile("data.dat", "rwd");
//            byte[] b = new byte[outputBytes.length];
//            raf.read(b);
//            System.out.println(new String(b));
//
//            long int1 = raf.readInt();
//            long int2 = raf.readInt();
//            System.out.println(int1);
//            System.out.println(int2);

//            RandomAccessFile raf = new RandomAccessFile("data.dat", "rwd");
//            FileChannel channel = raf.getChannel();
//            outputBytes[0] = 'a';
//            outputBytes[1] = 'b';
//            buffer.flip();
//            long numBytesRead = channel.read(buffer);
//            if (buffer.hasArray()) {
//                System.out.println("byte buffer = " + new String(buffer.array()));
////                System.out.println("byte buffer = " + new String(outputBytes));
//            }
////            System.out.println("output bytes = " + new String(outputBytes));
//
//            //  RELATIVE READ
////            intBuffer.flip();
////            numBytesRead = channel.read(intBuffer);
////            intBuffer.flip();
////            System.out.println(intBuffer.getInt());
////            intBuffer.flip();
////            numBytesRead = channel.read(intBuffer);
////            intBuffer.flip();
////            System.out.println(intBuffer.getInt());
//
//
//            // ABSOLUTE READ
//            numBytesRead = channel.read(intBuffer.position(0));
//            System.out.println(intBuffer.getInt(0));
//            numBytesRead = channel.read(intBuffer.position(0));
//            System.out.println(intBuffer.getInt(0));

//            channel.close();
//            raf.close();

        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        */
    }
}

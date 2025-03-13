/*
Implement the Unix Tail -N Command
*/

package com.example.sample;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.*;

public class TailCommand {

    public static void tail(String filePath, int n) throws IOException {
        Deque<String> deque = new ArrayDeque<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while((line = reader.readLine()) != null) {
                if(deque.size() == n) {
                    deque.pollFirst();
                }
                deque.addLast(line);
            }
        }

        for(String line : deque) {
            System.out.println(line);
        }
    }

    public static void tailOptimized(String filePath, int n) throws IOException {
        RandomAccessFile file = new RandomAccessFile(filePath, "r");
        long fileLength = file.length();
        long pos = fileLength - 1;
        int lineCount = 0;
        StringBuilder sb = new StringBuilder();
        List<String> lastNLines = new ArrayList<>(n);

        while(pos >= 0 && lineCount < n) {
            file.seek(pos);
            char c = (char) file.read();
            if(c == '\n') {
                lineCount++;
                lastNLines.add(sb.reverse().toString());
            } else {
                sb.append(c);
            }
            pos--;
        }

        if(sb.length() > 0) {
            lastNLines.add(sb.reverse().toString());
        }

        file.close();

        Collections.reverse(lastNLines);
        for(String line : lastNLines) {
            System.out.println(line);
        }
    }

    public static void main(String[] args) {
        try {
            String filePath = "logs/sample.log";
            int n = 10;
            System.out.println("Using BufferedReader:");
            tailOptimized(filePath, n);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

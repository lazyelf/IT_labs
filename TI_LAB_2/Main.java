package com.lazyelf;

import com.lazyelf.count.Counter;

public class Main {

    public static void printAuthorInformation() {
        System.out.print("\nAuthor: Mykhailova Viktoriia\n" +
                "2 course of Computer Science, group 201");
    }

    public static void main(String[] args) {
        Counter counter;
        if (args.length > 0) {
            counter = new Counter(args[0]);
        } else {
            counter = new Counter();
        }
        counter.print();
        counter.printCoding();
        counter.printCode();
        printAuthorInformation();
    }
}
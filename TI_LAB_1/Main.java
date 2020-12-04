package com.lazyelf;

import com.lazyelf.count.Counter;

public class Main {

    public static void main(String[] args) {
        Counter counter = new Counter(args[0]);
        counter.print();
    }
}



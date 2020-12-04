package com.lazyelf.count;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Counter {
    int[] letters = new int[26];
    double[] p_alpha = new double[26];
    double[] info = new double[26];
    int amount;
    double average_p;
    int alphabet_amount = 26;
    double entropy;
    double informationAmount = 0;

    public Counter(String path) {

        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(new File(path)));

            int c;
            while ((c = reader.read()) != -1) {
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    if (c >= 'a')
                        ++(letters[c - 'a']);
                    else
                        ++(letters[c - 'A']);
                    ++amount;
                }
            }

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        for (int i : letters) {
            if (i == 0) {
                --alphabet_amount;
            }
        }
        calculatePAlpha();
        calculateAverageP();
        calculateInfo();
        calculateInformationAmount();
        calculateEntropy();
    }

    private void calculateAverageP() {
        for (int i = 0; i < 26; ++i) {
            average_p += p_alpha[i];
        }
        average_p /= alphabet_amount;
    }

    private void calculateInfo() {
        for (int i = 0; i < 26; ++i) {
            if (p_alpha[i] != 0) {
                info[i] = -Math.log(p_alpha[i]) / Math.log(2);
            }
        }
    }

    private void calculatePAlpha() {
        for (int i = 0; i < 26; ++i) {
            p_alpha[i] = (double) letters[i] / amount;
        }
    }

    private void calculateEntropy() {
        for (int i = 0; i < 26; ++i) {
            if (letters[i] != 0) {
                entropy += p_alpha[i] * info[i];
            }
        }
    }

    private void calculateInformationAmount() {
        for (int i = 0; i < 26; ++i) {
            informationAmount += info[i];
        }
    }

    public void print() {
        for (int i = 0; i < 26; ++i) {
            if (letters[i] != 0) {
                System.out.printf("p(%c) = %.4f\t\tI(%c) = %6.4f bit\t\t", ((char) (i + 'a')), p_alpha[i], ((char) (i + 'a')), info[i]);
                System.out.printf("H(%c) = %.4f bit/character\n", ((char) (i + 'a')), (p_alpha[i] * info[i]));
            }
        }
        System.out.printf("\nInformation amount is %.4f\n", informationAmount);
        System.out.printf("\nAverage probability is %.4f\n", average_p);
        System.out.printf("\nEntropy is %.4f\n", entropy);
        System.out.printf("\nAuthor: Mykhailova Viktoriia\n");
    }
}

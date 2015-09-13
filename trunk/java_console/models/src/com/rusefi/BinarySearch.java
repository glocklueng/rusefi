package com.rusefi;

import java.util.Arrays;

public class BinarySearch {

    public static int binarySearch(double target, double[] angles) {
        int javaResult = Arrays.binarySearch(angles, 0, angles.length, target);

        System.out.println("Testing " + target);

        if (1 == 1) {
            if (javaResult < 0)
                return -2 - javaResult;
            if (target == angles[0])
                return 0;
            return javaResult;
        }

        int middle;
        int left = 0;
        int right = angles.length - 1;

        while (true) {
            middle = (left + right) / 2;
            System.out.println("l=" + left + ", m=" + middle + ", r=" + right);
            double angle = angles[middle];

            if (middle == left) {
                return middle;
            }
            if (target < angle) {
                right = middle;
            } else if (target > angle) {
                left = middle;
            } else {
                return middle;
            }
        }
    }
}
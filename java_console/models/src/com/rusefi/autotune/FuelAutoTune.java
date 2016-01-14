package com.rusefi.autotune;

import com.rusefi.config.Fields;

import java.util.Collection;

/**
 * 1/5/2016
 * (c) Andrey Belomutskiy 2013-2016
 */
public class FuelAutoTune {
    // todo: eliminate this
    // Fields.FUEL_RPM_COUNT
    // Fields.FUEL_LOAD_COUNT
    private static final int SIZE = 16;

    private static boolean isLogEnabled() {
        return true;
    }

//    private static final int TEMP_CORR = 39;


    public static class stDataOnline {
        public final double AFR;
        int rpmIndex;
        int engineLoadIndex;

        public stDataOnline(double AFR, int rpmIndex, int engineLoadIndex) {
            if (rpmIndex < 0 || rpmIndex >= Fields.FUEL_RPM_COUNT)
                throw new IllegalStateException("rpmIndex " + rpmIndex);
            if (engineLoadIndex < 0 || engineLoadIndex >= Fields.FUEL_LOAD_COUNT)
                throw new IllegalStateException("engineLoadIndex " + engineLoadIndex);
            this.AFR = AFR;
            this.rpmIndex = rpmIndex;
            this.engineLoadIndex = engineLoadIndex;
        }

        public static stDataOnline valueOf(double AFR, int rpm, double engineLoad) {
            int rpmIndex = (int) (rpm / 7000.0 * SIZE);
            if (rpmIndex < 0 || rpmIndex >= Fields.FUEL_RPM_COUNT)
                return null;
            int engineLoadIndex = (int) (engineLoad / 120.0 * SIZE);
            return new stDataOnline(AFR, rpmIndex, engineLoadIndex);
        }

        int getRpmIndex() {
            return rpmIndex;
        }

        private int getEngineLoadIndex() {
            return (int) engineLoadIndex;
        }

        public int PRESS_RT_32() {
            return getEngineLoadIndex();
        }

        public int RPM_RT_32() {
            return getRpmIndex();
        }
    }

    public static class Result {
        private final double[][] kgbcRES;

        public Result(double[][] kgbcRES) {
            this.kgbcRES = kgbcRES;
        }

        public double[][] getKgbcRES() {
            return kgbcRES;
        }
    }

    // void MainWindow::calckGBC(double STEP)
    public static Result process(boolean smooth, Collection<stDataOnline> dataECU, double STEP, double targetAFR) {
        double kgbcSQ[][] = new double[SIZE][SIZE];
        double kgbcSQsum = 0;
        double kgbcSQsumLast;
        double minSQ;
        double step;
        double minSQtotal = 1e+15;
        double kgbcSQsumLastTotal = 1e+16;
        double ksq = 1000; //???? ??????????????????? ??????????
        double ke = 100; //???? ??????????
        double kg = 100; //???? ?????


        // let's could how many data points we have for each cell
        int bkGBC[][] = new int[Fields.FUEL_LOAD_COUNT][Fields.FUEL_RPM_COUNT];
        for (stDataOnline data : dataECU) {
            bkGBC[data.PRESS_RT_32()][data.RPM_RT_32()]++;
        }
        // todo: add a comment what is this?
        double kgbcRES[][] = new double[Fields.FUEL_LOAD_COUNT][Fields.FUEL_RPM_COUNT];
        double kgbcINIT[][] = new double[Fields.FUEL_LOAD_COUNT][Fields.FUEL_RPM_COUNT];

        for (int engineLoadIndex = 0; engineLoadIndex < Fields.FUEL_LOAD_COUNT; engineLoadIndex++) {
            for (int rpmIndex = 0; rpmIndex < Fields.FUEL_RPM_COUNT; rpmIndex++) {
                kgbcINIT[engineLoadIndex][rpmIndex] = 1;
                kgbcRES[engineLoadIndex][rpmIndex] = 1;
            }
        }
//        double addGbcTwatRES[] = new double[TEMP_CORR];
//        double addGbcTwatINIT[] = new double[TEMP_CORR];
//
//        double addGbcTwatINIT_190[] = new double[191];
//        double addGbcTwatRES_190[] = new double[191];
//        double mulGbcTwatRES[] = new double[TEMP_CORR];
//        double mulGbcTwatINIT[] = new double[TEMP_CORR];
//        double mulGbcTwatINIT_190[] = new double[191];
//        double mulGbcTwatRES_190[] = new double[191];

//        for (int i = 0; i < 39; i++) {
//            addGbcTwatINIT[i] = 1;
//            addGbcTwatRES[i] = 1;
//        }

        double ktgbcRES[][] = new double[SIZE][SIZE];
        double ktgbcINIT[][] = new double[SIZE][SIZE];

        for (int i = 0; i < SIZE; i++) {          //trt
            for (int j = 0; j < SIZE; j++) {      //rpm
                ktgbcINIT[i][j] = 1;
                ktgbcRES[i][j] = 1;
            }
        }

        int gMinRT = 20; // minimal number of measurments in cell to be considered

        int minK = 0; // todo: what is this?
        while (true) {
            for (int r = 0; r < SIZE; r++) {
                for (int c = 0; c < SIZE; c++) {
                    if (bkGBC[r][c] < gMinRT)
                        continue;

                    //log("Processing " + r + "/c" + c);

                    minSQ = 1e+16;
                    kgbcSQsum = 1e+16;
                    step = STEP;
                    double mink = 0;
                    while (true) {
                        ////////////////////////////////////
                        //????????? ?????????? ? ????????
                        for (int i = 0; i < SIZE; i++) {
                            for (int j = 0; j < SIZE; j++) {
                                kgbcSQ[i][j] = 0;
                            }
                        }
                        kgbcSQsumLast = kgbcSQsum;

                        countDeviation(dataECU, kgbcSQ, kgbcRES, kgbcINIT, targetAFR);

                        kgbcSQsum = sumArray(kgbcSQ);

                        if (smooth) {
                            kgbcSQsum = smooth(kgbcSQsum, ksq, ke, kg, kgbcRES);
                        }
                        ////////////////////////////////////
                        if (kgbcSQsum >= kgbcSQsumLast)
                            step = -step;
                        //???? ?????? ?? ??????? ????? ???, ?? ? ?? ?????????? ??
                    /*if(bkGBC[r][c]) */

//                        log("Adjusting " + step);
                        kgbcRES[r][c] += step;
                        if (kgbcSQsum < minSQ)
                            minSQ = kgbcSQsum;

                        if (Math.abs(minSQ - kgbcSQsumLast) < 1e-10)
                            mink++;
                        if (mink > 4) {
//                            updateTablekGBC();
//                            ui -> statusBar -> showMessage(QString::number (kgbcSQsum), 500);
                            log("break " + c + "/" + r);
                            break;
                        }
                    }
                }
            }
            if (kgbcSQsum < minSQtotal)
                minSQtotal = kgbcSQsum;
            if (Math.abs(minSQtotal - kgbcSQsumLastTotal) < 1e-10)
                minK++;
            if (minK > 4) {
                //updateTablekGBC();
                //ui->statusBar->showMessage(QString::number(kgbcSQsum), 500);
                log("return " + minK);
                return new Result(kgbcRES);
            }
            kgbcSQsumLastTotal = kgbcSQsum;
            //ui->statusBar->showMessage(QString::number(gbcSQsum));
            //updateTableGBC();

        }
    }

    private static void countDeviation(Collection<stDataOnline> dataECU, double[][] kgbcSQ, double[][] kgbcRES, double[][] kgbcINIT, double targetAFR) {
        for (stDataOnline dataPoint : dataECU) {
            double corrInit = 1; // addGbcTwatINIT_190[dataPoint.twat + 40];
            double corrRes = 1; //addGbcTwatRES_190[dataPoint.twat + 40];
            double tpsCorrInit = 1; //ktgbcINIT[dataPoint.THR_RT_16][dataPoint.RPM_RT_32()];
            double tpsCorrRes = 1; //ktgbcRES[dataPoint.THR_RT_16][dataPoint.RPM_RT_32()];

            double ALF = targetAFR / 14.7;
            double tmp = (dataPoint.AFR / 14.7 - ALF * (kgbcRES[dataPoint.PRESS_RT_32()][dataPoint.RPM_RT_32()] * tpsCorrRes * corrRes) /
                    (kgbcINIT[dataPoint.PRESS_RT_32()][dataPoint.RPM_RT_32()] * tpsCorrInit * corrInit));

//            if (isLogEnabled())
//                log("r=" + r + "/c=" + c + ": tmp=" + tmp);

            kgbcSQ[dataPoint.PRESS_RT_32()][dataPoint.RPM_RT_32()] += tmp * tmp;
        }
    }

    private static double sumArray(double[][] kgbcSQ) {
        double kgbcSQsum = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                kgbcSQsum += kgbcSQ[i][j];
            }
        }
        return kgbcSQsum;
    }

    private static double smooth(double kgbcSQsum, double ksq, double ke, double kg, double[][] kgbcRES) {
        double e;
        double g;
        kgbcSQsum = ksq * kgbcSQsum;
        e = 0;
        // todo: add a comment while 'SIZE - 1' here?
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE; j++) {
                double tmp = kgbcRES[i][j] - kgbcRES[i + 1][j];
                e += tmp * tmp;
                tmp = kgbcRES[j][i] - kgbcRES[j][i + 1];
                e += tmp * tmp;
            }
        }
        g = 0;
        for (int i = 0; i < SIZE - 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                double tmp = kgbcRES[i][j] - 2 * kgbcRES[i + 1][j] + kgbcRES[i + 2][j];
                g += tmp * tmp;
                tmp = kgbcRES[j][i] - 2 * kgbcRES[j][i + 1] + kgbcRES[j][i + 2];
                g += tmp * tmp;
            }
        }
        kgbcSQsum += ke * e + kg * g;
        return kgbcSQsum;
    }

    private static void log(String s) {
        System.out.println(s);
    }

}

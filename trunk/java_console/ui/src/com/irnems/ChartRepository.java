package com.irnems;

import java.util.ArrayList;
import java.util.List;

/**
 * 7/27/13
 * (c) Andrey Belomutskiy
 */
public class ChartRepository {
    private static final ChartRepository instance = new ChartRepository();

    private final List<String> charts = new ArrayList<String>();

    private ChartRepository() {
    }

    public static ChartRepository getInstance() {
        return instance;
    }

    public String getChart(int index) {
        return charts.get(index);
    }

    public int getSize() {
        return charts.size();
    }

    public void addChart(String value) {
        charts.add(value);
    }
}

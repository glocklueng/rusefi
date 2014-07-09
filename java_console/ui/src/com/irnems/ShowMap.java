package com.irnems;

import com.irnems.file.BaseMap;
import com.irnems.models.XYData;
import com.rusefi.ui.FrameHelper;
import com.rusefi.ui.ChartHelper;

import javax.swing.*;

/**
 * 7/18/13
 * (c) Andrey Belomutskiy
 */
public class ShowMap extends FrameHelper {
    public static void main(String[] args) {
//        XYData data = BaseMap.loadData("a.csv", "maf", "af");
//        XYData data2 = BaseMap.loadData("a.csv", "maf", "table_fuel");

        XYData data = BaseMap.loadData("200.csv", "maf", "dwell");
        XYData data2 = null;

        JPanel jsp = ChartHelper.create3DControl(data, ChartHelper.createDefaultSurfaceModel(data, data2), "MAF<>Fuel Map");

        new ShowMap().showFrame(jsp);
    }
}

package com.romraider.maps;

import com.romraider.Settings;
import com.romraider.xml.RomAttributeParser;

import java.awt.*;

/**
 * (c) Andrey Belomutskiy
 * 6/20/2015.
 */
public abstract class TableWithData extends Table {
    public void setData(DataCell[] data) {
        this.data = data;
    }

    public DataCell getDataCell(int location) {
        return data[location];
    }

    public void horizontalInterpolate() {
        int[] coords = {getDataSize(), 0};
        DataCell[] tableData = getData();

        int y;
        for (y = 0; y < getDataSize(); y++) {
            if (tableData[y].isSelected()) {
                if (y < coords[0])
                    coords[0] = y;
                if (y > coords[1])
                    coords[1] = y;
            }
        }
        if (coords[1] - coords[0] > 1) {
            double diff = (tableData[coords[0]].getRealValue() - tableData[coords[1]].getRealValue()) / (coords[1] - coords[0]);
            if (Math.abs(diff) > 0) {
                for (y = coords[0] + 1; y < coords[1]; y++)
                    data[y].setRealValue(String.valueOf(tableData[y - 1].getRealValue() - diff));
            }
        }
    }

    public void populateTable(byte[] input, int romRamOffset) {
        // temporarily remove lock
        boolean tempLock = locked;
        locked = false;

        if (!beforeRam) {
            this.ramOffset = romRamOffset;
        }

        for (int i = 0; i < data.length; i++) {
            if (data[i] == null) {
                double dataValue = 0.0;

                // populate data cells
                if (storageType == Settings.STORAGE_TYPE_FLOAT) { //float storage type
                    byte[] byteValue = new byte[4];
                    byteValue[0] = input[getStorageAddress() + i * 4 - ramOffset];
                    byteValue[1] = input[getStorageAddress() + i * 4 - ramOffset + 1];
                    byteValue[2] = input[getStorageAddress() + i * 4 - ramOffset + 2];
                    byteValue[3] = input[getStorageAddress() + i * 4 - ramOffset + 3];
                    dataValue = RomAttributeParser.byteToFloat(byteValue, endian);

                } else { // integer storage type
                    dataValue = RomAttributeParser.parseByteValue(input,
                            endian,
                            getStorageAddress() + i * storageType - ramOffset,
                            storageType,
                            signed);
                }

                data[i] = new DataCell(this, dataValue, 0, i);
                data[i].setPreferredSize(new Dimension(cellWidth, cellHeight));
                centerPanel.add(data[i]);

                // show locked cell
                if (tempLock) {
                    data[i].setForeground(Color.GRAY);
                }
            }
        }

        // reset locked status
        locked = tempLock;
        calcCellRanges();
    }
}

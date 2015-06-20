package com.romraider.maps;

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

}

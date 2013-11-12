package com.irnems.waves;

/**
 * 7/7/13
 * (c) Andrey Belomutskiy
 */
public interface ZoomProvider {
    ZoomProvider DEFAULT = new ZoomProvider() {
        @Override
        public double getZoomValue() {
            return 1;
        }
    };

    double getZoomValue();
}

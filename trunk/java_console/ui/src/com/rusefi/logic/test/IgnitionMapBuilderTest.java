package com.rusefi.logic.test;

import com.rusefi.logic.IgnitionMapBuilder;
import org.junit.Test;

import static com.rusefi.logic.IgnitionMapBuilder.ChamberStyle.*;
import static com.rusefi.logic.IgnitionMapBuilder.getTopAdvanceForBore;
import static junit.framework.Assert.assertEquals;

/**
 * (c) Andrey Belomutskiy 2012-2015
 * 12/24/2015
 */
public class IgnitionMapBuilderTest {
    @Test
    public void testIgnitionMapBuilder() {
        assertEquals(35.0, getTopAdvanceForBore(OPEN_CHAMBER, 98, 8));
        assertEquals(33.0, getTopAdvanceForBore(OPEN_CHAMBER, 98, 11));

        assertEquals(22.0, getTopAdvanceForBore(SWITL_TUMBLE, 89, 9));
    }
}

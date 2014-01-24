package com.rusefi.pcb.test;


import com.rusefi.misc.ChangesModel;
import org.junit.Test;

import java.util.Arrays;

import static junit.framework.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * @author Andrey Belomutskiy
 *         1/24/14
 */
public class ChangesModelTest {
    @Test
    public void testConfigParser() {

        ChangesModel model = ChangesModel.getInstance();
        model.clear();

        model.read(Arrays.asList("reMove    c1", "add mmc_usb_1.kicad_pcb",
                "adD mmc_usb_1.kicad_pcb 4 4"));

        assertEquals(1, model.DEL_REQUESTS.size());
        assertTrue(model.DEL_REQUESTS.contains("C1"));


        assertEquals(2, model.ADD_REQUESTS.size());


    }
}

package com.rusefi.waves.test;

import com.rusefi.waves.WaveReport;
import com.rusefi.waves.ZoomProvider;
import org.junit.Test;

import static junit.framework.Assert.assertEquals;

/**
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 */
public class WaveReportTest {
    public static final String report = "u!14679!d!15991!u!16823!d!18134!u!18965!d!20278!u!21108!d!22420!u!23251!d!24563!u!25394!d!26706!u!27536!d!28850!u!29678!d!30991!u!31822!d!33134!u!33965!d!35277!u!36108!d!37420!u!38251!d!39563!u!40394!d!41706!u!42537!d!43849!";

    @Test
    public void testParse() {
        WaveReport wr = new WaveReport(report);
        assertEquals(14, wr.getList().size());

        assertEquals(14679, wr.getMinTime());
        assertEquals(43849, wr.getMaxTime());

        assertEquals(59, wr.timeToScreen(18134, 500, ZoomProvider.DEFAULT));
    }
}

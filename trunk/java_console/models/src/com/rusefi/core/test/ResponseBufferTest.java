package com.rusefi.core.test;

import com.rusefi.core.ResponseBuffer;
import com.rusefi.io.LinkDecoder;
import org.junit.Test;

import java.util.concurrent.atomic.AtomicReference;

import static org.junit.Assert.*;

/**
 * @author Andrey Belomutskiy
 *         12/26/12
 * @see ResponseBuffer
 */
public class ResponseBufferTest {
    @Test
    public void testSingleLine() {
        final AtomicReference<String> currentReference = new AtomicReference<>();

        ResponseBuffer rb = new ResponseBuffer(new ResponseBuffer.ResponseListener() {
            public void onResponse(String response) {
                currentReference.set(response);
            }
        });
        rb.append("\r", LinkDecoder.TEXT_PROTOCOL_DECODER);
        assertNull(currentReference.get());
        rb.append("\n", LinkDecoder.TEXT_PROTOCOL_DECODER);
        assertNull(currentReference.get());

        rb.append("hi\n", LinkDecoder.TEXT_PROTOCOL_DECODER);
        assertEquals("hi", currentReference.get());

        rb.append("\r\n\r\n\r\nhi2\n\n\n", LinkDecoder.TEXT_PROTOCOL_DECODER);
        assertEquals("hi2", currentReference.get());
    }
}

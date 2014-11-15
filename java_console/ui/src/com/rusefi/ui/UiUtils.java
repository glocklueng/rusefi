package com.rusefi.ui;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * 7/7/13
 * (c) Andrey Belomutskiy
 */
public class UiUtils {
    public static void saveImageWithPrompt(String fileName, Component parent, Component component) {
        JFileChooser fc = new JFileChooser();
        FileFilter filter = new FileNameExtensionFilter("PNG files", "png");
        fc.setFileFilter(filter);
        fc.addChoosableFileFilter(filter);
        fc.setSelectedFile(new File(fileName));
        if (fc.showSaveDialog(parent) == JFileChooser.APPROVE_OPTION) {
            fileName = fc.getSelectedFile().getAbsolutePath();
            UiUtils.saveImage(fileName, component);
        }
    }

    public static void saveImage(String fileName, Component component) {
        BufferedImage img = getScreenShot(component);
        try {
            ImageIO.write(img, "png", new File(fileName));
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    private static BufferedImage getScreenShot(Component component) {
        // http://stackoverflow.com/questions/5853879/swing-obtain-image-of-jframe/5853992
        BufferedImage image = new BufferedImage(component.getWidth(), component.getHeight(), BufferedImage.TYPE_INT_RGB);
        // call the Component's paint method, using
        // the Graphics object of the image.
        component.paint(image.getGraphics());
        return image;
    }

    public static void setPauseButtonText(JButton pauseButton, boolean isPaused) {
        pauseButton.setText(isPaused ? "resume" : "pause");
    }

    public static void centerWindow(Window w) {
        w.pack();
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameSize = w.getSize();
        w.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
    }
}

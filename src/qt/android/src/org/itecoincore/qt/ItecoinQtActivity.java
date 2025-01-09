package org.Itecoincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class ItecoinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File ItecoinDir = new File(getFilesDir().getAbsolutePath() + "/.Itecoin");
        if (!ItecoinDir.exists()) {
            ItecoinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}

package com.example.minigolfappfinal;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /** Called when the user taps the Play! button */
    public void sendToScreen2(View view) {
        Intent intent = new Intent(this, Screen2Activity.class);
        startActivity(intent);
    }

    /** Called when the user taps the Play! button */
    public void sendToHistory(View view) {
        Intent intent = new Intent(this, HistoryActivity.class);
        startActivity(intent);
    }
}
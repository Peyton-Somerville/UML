package com.example.minigolfappfinal;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class LocationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_location);
    }

    /** Called when the user taps the back button */
    public void backToScreen2(View view) {
        Intent intent = new Intent(this, Screen2Activity.class);
        startActivity(intent);
    }
}

package com.example.minigolfappfinal;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class Screen2Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_screen2);
    }

    /** Called when the user taps the 'Go Straight to the Game!' button */
    public void sendToScorecard(View view) {
        Intent intent = new Intent(this, ScorecardActivity.class);
        startActivity(intent);
    }

    /** Called when the user taps the 'Find Courses Near You' button */
    public void sendToLocation(View view) {
        Intent intent = new Intent(this, LocationActivity.class);
        startActivity(intent);
    }

    /** Called when the user taps the back button */
    public void backToMain(View view) {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}

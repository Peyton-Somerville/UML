package com.example.minigolfappfinal;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class SettingsActivity extends AppCompatActivity {

    EditText edTxtStrLim;
    EditText edTxtStrPen;

    String strLim = "8";
    String strPen = "2";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        edTxtStrLim = findViewById(R.id.editTxtStrLim);
        edTxtStrPen = findViewById(R.id.editTxtStrPen);

        SharedPreferences settings = getSharedPreferences("settings", 0);
        strLim = settings.getString("strokeLim", "");
        strPen = settings.getString("strokePen", "");
        edTxtStrLim.setText(strLim);
        edTxtStrPen.setText(strPen);
    }

    /** Called when the user leaves the settings */
    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences sharedPreferences = getSharedPreferences("settings", 0);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        if(edTxtStrLim.getText().length() == 0)
            editor.putString("strokeLim", "8");
        else {
            if (Integer.parseInt(edTxtStrLim.getText().toString()) < 8)
                editor.putString("strokeLim", "8");
            else if (Integer.parseInt(edTxtStrLim.getText().toString()) > 12)
                editor.putString("strokeLim", "12");
            else
                editor.putString("strokeLim", edTxtStrLim.getText().toString());
        }

        if(edTxtStrPen.getText().length() == 0)
            editor.putString("strokePen", "2");
        else {
            if(Integer.parseInt(edTxtStrPen.getText().toString()) > 50)
                editor.putString("strokePen", "50");
            else
                editor.putString("strokePen", edTxtStrPen.getText().toString());
        }

        editor.apply();
        Toast.makeText(SettingsActivity.this, "Settings Saved", Toast.LENGTH_SHORT).show();
    }

    /** Called when the user taps the back button */
    public void backToScorecard(View view) {
        Intent intent = new Intent(this, ScorecardActivity.class);
        startActivity(intent);
    }

    /** Called when the user taps the android back button */
    @Override
    public void onBackPressed() {
        Intent intent = new Intent(this, ScorecardActivity.class);
        startActivity(intent);
    }
}

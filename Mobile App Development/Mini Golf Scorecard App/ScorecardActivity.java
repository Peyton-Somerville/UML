package com.example.minigolfappfinal;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.Toast;

public class ScorecardActivity extends AppCompatActivity {

    Button btn11;
    Button btn12;
    Button btn13;
    Button btn14;

    Button btn21;
    Button btn22;
    Button btn23;
    Button btn24;

    Button btn31;
    Button btn32;
    Button btn33;
    Button btn34;

    Button btn41;
    Button btn42;
    Button btn43;
    Button btn44;

    Button btn51;
    Button btn52;
    Button btn53;
    Button btn54;

    Button btn61;
    Button btn62;
    Button btn63;
    Button btn64;

    Button btn71;
    Button btn72;
    Button btn73;
    Button btn74;

    Button btn81;
    Button btn82;
    Button btn83;
    Button btn84;

    Button btn91;
    Button btn92;
    Button btn93;
    Button btn94;

    Button btn101;
    Button btn102;
    Button btn103;
    Button btn104;

    Button btn111;
    Button btn112;
    Button btn113;
    Button btn114;

    Button btn121;
    Button btn122;
    Button btn123;
    Button btn124;

    Button btn131;
    Button btn132;
    Button btn133;
    Button btn134;

    Button btn141;
    Button btn142;
    Button btn143;
    Button btn144;

    Button btn151;
    Button btn152;
    Button btn153;
    Button btn154;

    Button btn161;
    Button btn162;
    Button btn163;
    Button btn164;

    Button btn171;
    Button btn172;
    Button btn173;
    Button btn174;

    Button btn181;
    Button btn182;
    Button btn183;
    Button btn184;

    Button btnTotP1;
    Button btnTotP2;
    Button btnTotP3;
    Button btnTotP4;

    Button btnScore9;
    Button btnScore10;
    Button btnScore11;
    Button btnScore12;

    Button btnBack;
    Button btnReset;

    String score;
    int boxNum;
    int p1Total = 0, p2Total = 0, p3Total = 0, p4Total = 0;
    int intScore;

    String stringStrLim = "8";
    String stringStrPen = "2";
    int strLim;
    int strPen;

    TableLayout scoreSelect;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scorecard);

        btn11 = findViewById(R.id.button11);
        btn12 = findViewById(R.id.button12);
        btn13 = findViewById(R.id.button13);
        btn14 = findViewById(R.id.button14);

        btn21 = findViewById(R.id.button21);
        btn22 = findViewById(R.id.button22);
        btn23 = findViewById(R.id.button23);
        btn24 = findViewById(R.id.button24);

        btn31 = findViewById(R.id.button31);
        btn32 = findViewById(R.id.button32);
        btn33 = findViewById(R.id.button33);
        btn34 = findViewById(R.id.button34);

        btn41 = findViewById(R.id.button41);
        btn42 = findViewById(R.id.button42);
        btn43 = findViewById(R.id.button43);
        btn44 = findViewById(R.id.button44);

        btn51 = findViewById(R.id.button51);
        btn52 = findViewById(R.id.button52);
        btn53 = findViewById(R.id.button53);
        btn54 = findViewById(R.id.button54);

        btn61 = findViewById(R.id.button61);
        btn62 = findViewById(R.id.button62);
        btn63 = findViewById(R.id.button63);
        btn64 = findViewById(R.id.button64);

        btn71 = findViewById(R.id.button71);
        btn72 = findViewById(R.id.button72);
        btn73 = findViewById(R.id.button73);
        btn74 = findViewById(R.id.button74);

        btn81 = findViewById(R.id.button81);
        btn82 = findViewById(R.id.button82);
        btn83 = findViewById(R.id.button83);
        btn84 = findViewById(R.id.button84);

        btn91 = findViewById(R.id.button91);
        btn92 = findViewById(R.id.button92);
        btn93 = findViewById(R.id.button93);
        btn94 = findViewById(R.id.button94);

        btn101 = findViewById(R.id.button101);
        btn102 = findViewById(R.id.button102);
        btn103 = findViewById(R.id.button103);
        btn104 = findViewById(R.id.button104);

        btn111 = findViewById(R.id.button111);
        btn112 = findViewById(R.id.button112);
        btn113 = findViewById(R.id.button113);
        btn114 = findViewById(R.id.button114);

        btn121 = findViewById(R.id.button121);
        btn122 = findViewById(R.id.button122);
        btn123 = findViewById(R.id.button123);
        btn124 = findViewById(R.id.button124);

        btn131 = findViewById(R.id.button131);
        btn132 = findViewById(R.id.button132);
        btn133 = findViewById(R.id.button133);
        btn134 = findViewById(R.id.button134);

        btn141 = findViewById(R.id.button141);
        btn142 = findViewById(R.id.button142);
        btn143 = findViewById(R.id.button143);
        btn144 = findViewById(R.id.button144);

        btn151 = findViewById(R.id.button151);
        btn152 = findViewById(R.id.button152);
        btn153 = findViewById(R.id.button153);
        btn154 = findViewById(R.id.button154);

        btn161 = findViewById(R.id.button161);
        btn162 = findViewById(R.id.button162);
        btn163 = findViewById(R.id.button163);
        btn164 = findViewById(R.id.button164);

        btn171 = findViewById(R.id.button171);
        btn172 = findViewById(R.id.button172);
        btn173 = findViewById(R.id.button173);
        btn174 = findViewById(R.id.button174);

        btn181 = findViewById(R.id.button181);
        btn182 = findViewById(R.id.button182);
        btn183 = findViewById(R.id.button183);
        btn184 = findViewById(R.id.button184);

        scoreSelect = findViewById(R.id.tableScoreSelect);
        btnBack = findViewById(R.id.btnBack);
        btnReset = findViewById(R.id.btnReset);

        btnTotP1 = findViewById(R.id.buttonScoreP1);
        btnTotP2 = findViewById(R.id.buttonScoreP2);
        btnTotP3 = findViewById(R.id.buttonScoreP3);
        btnTotP4 = findViewById(R.id.buttonScoreP4);

        btnScore9 = findViewById(R.id.btnScore9);
        btnScore10 = findViewById(R.id.btnScore10);
        btnScore11 = findViewById(R.id.btnScore11);
        btnScore12 = findViewById(R.id.btnScore12);

        boolean checkFirstRun = getSharedPreferences("pref", MODE_PRIVATE).getBoolean("checkFirstRun", true);
        if(checkFirstRun) {
            getSharedPreferences("pref", MODE_PRIVATE).edit().putBoolean("checkFirstRun", false).apply();

            /*SharedPreferences initCardInfo = getSharedPreferences("cardInfo", 0);
            SharedPreferences.Editor e = initCardInfo.edit();

            e.putString("btn11", "");
            e.putString("btn12", "");
            e.putString("btn13", "");
            e.putString("btn14", "");

            e.putString("btn21", "");
            e.putString("btn22", "");
            e.putString("btn23", "");
            e.putString("btn24", "");

            e.putString("btnTotP1", "");
            e.putString("btnTotP2", "");
            e.putString("btnTotP3", "");
            e.putString("btnTotP4", "");

            e.apply(); */

            SharedPreferences initSettings = getSharedPreferences("settings", 0);
            SharedPreferences.Editor editor = initSettings.edit();

            editor.putString("strokeLim", "8");
            editor.putString("strokePen", "2");
            editor.apply();
        }

        SharedPreferences cardInfo = getSharedPreferences("cardInfo", 0);
        btn11.setText(cardInfo.getString("btn11", ""));
        btn12.setText(cardInfo.getString("btn12", ""));
        btn13.setText(cardInfo.getString("btn13", ""));
        btn14.setText(cardInfo.getString("btn14", ""));

        btn21.setText(cardInfo.getString("btn21", ""));
        btn22.setText(cardInfo.getString("btn22", ""));
        btn23.setText(cardInfo.getString("btn23", ""));
        btn24.setText(cardInfo.getString("btn24", ""));

        btn31.setText(cardInfo.getString("btn31", ""));
        btn32.setText(cardInfo.getString("btn32", ""));
        btn33.setText(cardInfo.getString("btn33", ""));
        btn34.setText(cardInfo.getString("btn34", ""));

        btn41.setText(cardInfo.getString("btn41", ""));
        btn42.setText(cardInfo.getString("btn42", ""));
        btn43.setText(cardInfo.getString("btn43", ""));
        btn44.setText(cardInfo.getString("btn44", ""));

        btn51.setText(cardInfo.getString("btn51", ""));
        btn52.setText(cardInfo.getString("btn52", ""));
        btn53.setText(cardInfo.getString("btn53", ""));
        btn54.setText(cardInfo.getString("btn54", ""));

        btn61.setText(cardInfo.getString("btn61", ""));
        btn62.setText(cardInfo.getString("btn62", ""));
        btn63.setText(cardInfo.getString("btn63", ""));
        btn64.setText(cardInfo.getString("btn64", ""));

        btn71.setText(cardInfo.getString("btn71", ""));
        btn72.setText(cardInfo.getString("btn72", ""));
        btn73.setText(cardInfo.getString("btn73", ""));
        btn74.setText(cardInfo.getString("btn74", ""));

        btn81.setText(cardInfo.getString("btn81", ""));
        btn82.setText(cardInfo.getString("btn82", ""));
        btn83.setText(cardInfo.getString("btn83", ""));
        btn84.setText(cardInfo.getString("btn84", ""));

        btn91.setText(cardInfo.getString("btn91", ""));
        btn92.setText(cardInfo.getString("btn92", ""));
        btn93.setText(cardInfo.getString("btn93", ""));
        btn94.setText(cardInfo.getString("btn94", ""));

        btn101.setText(cardInfo.getString("btn101", ""));
        btn102.setText(cardInfo.getString("btn102", ""));
        btn103.setText(cardInfo.getString("btn103", ""));
        btn104.setText(cardInfo.getString("btn104", ""));

        btn111.setText(cardInfo.getString("btn111", ""));
        btn112.setText(cardInfo.getString("btn112", ""));
        btn113.setText(cardInfo.getString("btn113", ""));
        btn114.setText(cardInfo.getString("btn114", ""));

        btn121.setText(cardInfo.getString("btn121", ""));
        btn122.setText(cardInfo.getString("btn122", ""));
        btn123.setText(cardInfo.getString("btn123", ""));
        btn124.setText(cardInfo.getString("btn124", ""));

        btn131.setText(cardInfo.getString("btn131", ""));
        btn132.setText(cardInfo.getString("btn132", ""));
        btn133.setText(cardInfo.getString("btn133", ""));
        btn134.setText(cardInfo.getString("btn134", ""));

        btn141.setText(cardInfo.getString("btn141", ""));
        btn142.setText(cardInfo.getString("btn142", ""));
        btn143.setText(cardInfo.getString("btn143", ""));
        btn144.setText(cardInfo.getString("btn144", ""));

        btn151.setText(cardInfo.getString("btn151", ""));
        btn152.setText(cardInfo.getString("btn152", ""));
        btn153.setText(cardInfo.getString("btn153", ""));
        btn154.setText(cardInfo.getString("btn154", ""));

        btn161.setText(cardInfo.getString("btn161", ""));
        btn162.setText(cardInfo.getString("btn162", ""));
        btn163.setText(cardInfo.getString("btn163", ""));
        btn164.setText(cardInfo.getString("btn164", ""));

        btn171.setText(cardInfo.getString("btn171", ""));
        btn172.setText(cardInfo.getString("btn172", ""));
        btn173.setText(cardInfo.getString("btn173", ""));
        btn174.setText(cardInfo.getString("btn174", ""));

        btn181.setText(cardInfo.getString("btn181", ""));
        btn182.setText(cardInfo.getString("btn182", ""));
        btn183.setText(cardInfo.getString("btn183", ""));
        btn184.setText(cardInfo.getString("btn184", ""));

        btnTotP1.setText(cardInfo.getString("btnTotP1", ""));
        btnTotP2.setText(cardInfo.getString("btnTotP2", ""));
        btnTotP3.setText(cardInfo.getString("btnTotP3", ""));
        btnTotP4.setText(cardInfo.getString("btnTotP4", ""));

        if(!btnTotP1.getText().toString().equals(""))
            p1Total = Integer.parseInt(btnTotP1.getText().toString());
        if(!btnTotP2.getText().toString().equals(""))
            p2Total = Integer.parseInt(btnTotP2.getText().toString());
        if(!btnTotP3.getText().toString().equals(""))
            p3Total = Integer.parseInt(btnTotP3.getText().toString());
        if(!btnTotP4.getText().toString().equals(""))
            p4Total = Integer.parseInt(btnTotP4.getText().toString());


        SharedPreferences settings = getSharedPreferences("settings", 0);
        stringStrLim = settings.getString("strokeLim", "");
        stringStrPen = settings.getString("strokePen", "");

        strLim = Integer.parseInt(stringStrLim);
        strPen = Integer.parseInt(stringStrPen);

        if(strLim == 9) {
            btnScore9.setVisibility(View.VISIBLE);
        }
        else if(strLim == 10) {
            btnScore9.setVisibility(View.VISIBLE);
            btnScore10.setVisibility(View.VISIBLE);
        }
        else if(strLim == 11) {
            btnScore9.setVisibility(View.VISIBLE);
            btnScore10.setVisibility(View.VISIBLE);
            btnScore11.setVisibility(View.VISIBLE);
        }
        else if(strLim == 12) {
            btnScore9.setVisibility(View.VISIBLE);
            btnScore10.setVisibility(View.VISIBLE);
            btnScore11.setVisibility(View.VISIBLE);
            btnScore12.setVisibility(View.VISIBLE);
        }
    }

    /** Called when the user taps a score box */
    public void sendToScoreInput(View view) {
        scoreSelect.setVisibility(View.VISIBLE);
        btnBack.setVisibility(View.INVISIBLE);
        btnReset.setVisibility(View.INVISIBLE);
        boxNum = view.getId();
    }

    /** Called when the user chooses a score */
    public void scoreInput(View view) {
        scoreSelect.setVisibility(View.INVISIBLE);
        btnBack.setVisibility(View.VISIBLE);
        btnReset.setVisibility(View.VISIBLE);

        switch(view.getId()) {
            case R.id.btnScore1:
                score = "1";
                break;
            case R.id.btnScore2:
                score = "2";
                break;
            case R.id.btnScore3:
                score = "3";
                break;
            case R.id.btnScore4:
                score = "4";
                break;
            case R.id.btnScore5:
                score = "5";
                break;
            case R.id.btnScore6:
                score = "6";
                break;
            case R.id.btnScore7:
                score = "7";
                break;
            case R.id.btnScore8:
                score = "8";
                break;
            case R.id.btnScore9:
                score = "9";
                break;
            case R.id.btnScore10:
                score = "10";
                break;
            case R.id.btnScore11:
                score = "11";
                break;
            case R.id.btnScore12:
                score = "12";
                break;
            case R.id.btnNoScore:
                score = "";
                break;
            case R.id.btnStrOut:
                score = String.valueOf(strLim + strPen);
            default:
                break;
        }

        if(score.equals(""))
            intScore = 0;
        else
            intScore = Integer.parseInt(score);

        switch (boxNum) {
            case R.id.button11:
                if(btn11.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn11.getText().toString());
                btn11.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button12:
                if(btn12.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn12.getText().toString());
                btn12.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button13:
                if(btn13.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn13.getText().toString());
                btn13.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button14:
                if(btn14.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn14.getText().toString());
                btn14.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button21:
                if(btn21.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn21.getText().toString());
                btn21.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button22:
                if(btn22.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn22.getText().toString());
                btn22.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button23:
                if(btn23.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn23.getText().toString());
                btn23.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button24:
                if(btn24.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn24.getText().toString());
                btn24.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button31:
                if(btn31.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn31.getText().toString());
                btn31.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button32:
                if(btn32.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn32.getText().toString());
                btn32.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button33:
                if(btn33.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn33.getText().toString());
                btn33.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button34:
                if(btn34.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn34.getText().toString());
                btn34.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button41:
                if(btn41.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn41.getText().toString());
                btn41.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button42:
                if(btn42.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn42.getText().toString());
                btn42.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button43:
                if(btn43.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn43.getText().toString());
                btn43.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button44:
                if(btn44.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn44.getText().toString());
                btn44.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button51:
                if(btn51.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn51.getText().toString());
                btn51.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button52:
                if(btn52.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn52.getText().toString());
                btn52.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button53:
                if(btn53.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn53.getText().toString());
                btn53.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button54:
                if(btn54.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn54.getText().toString());
                btn54.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button61:
                if(btn61.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn61.getText().toString());
                btn61.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button62:
                if(btn62.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn62.getText().toString());
                btn62.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button63:
                if(btn63.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn63.getText().toString());
                btn63.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button64:
                if(btn64.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn64.getText().toString());
                btn64.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button71:
                if(btn71.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn71.getText().toString());
                btn71.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button72:
                if(btn72.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn72.getText().toString());
                btn72.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button73:
                if(btn73.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn73.getText().toString());
                btn73.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button74:
                if(btn74.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn74.getText().toString());
                btn74.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button81:
                if(btn81.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn81.getText().toString());
                btn81.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button82:
                if(btn82.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn82.getText().toString());
                btn82.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button83:
                if(btn83.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn83.getText().toString());
                btn83.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button84:
                if(btn84.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn84.getText().toString());
                btn84.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button91:
                if(btn91.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn91.getText().toString());
                btn91.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button92:
                if(btn92.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn92.getText().toString());
                btn92.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button93:
                if(btn93.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn93.getText().toString());
                btn93.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button94:
                if(btn94.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn94.getText().toString());
                btn94.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button101:
                if(btn101.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn101.getText().toString());
                btn101.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button102:
                if(btn102.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn102.getText().toString());
                btn102.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button103:
                if(btn103.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn103.getText().toString());
                btn103.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button104:
                if(btn104.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn104.getText().toString());
                btn104.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button111:
                if(btn111.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn111.getText().toString());
                btn111.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button112:
                if(btn112.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn112.getText().toString());
                btn112.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button113:
                if(btn113.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn113.getText().toString());
                btn113.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button114:
                if(btn114.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn114.getText().toString());
                btn114.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button121:
                if(btn121.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn121.getText().toString());
                btn121.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button122:
                if(btn122.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn122.getText().toString());
                btn122.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button123:
                if(btn123.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn123.getText().toString());
                btn123.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button124:
                if(btn124.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn124.getText().toString());
                btn124.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button131:
                if(btn131.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn131.getText().toString());
                btn131.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button132:
                if(btn132.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn132.getText().toString());
                btn132.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button133:
                if(btn133.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn133.getText().toString());
                btn133.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button134:
                if(btn134.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn134.getText().toString());
                btn134.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button141:
                if(btn141.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn141.getText().toString());
                btn141.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button142:
                if(btn142.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn142.getText().toString());
                btn142.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button143:
                if(btn143.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn143.getText().toString());
                btn143.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button144:
                if(btn144.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn144.getText().toString());
                btn144.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button151:
                if(btn151.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn151.getText().toString());
                btn151.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button152:
                if(btn152.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn152.getText().toString());
                btn152.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button153:
                if(btn153.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn153.getText().toString());
                btn153.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button154:
                if(btn154.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn154.getText().toString());
                btn154.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button161:
                if(btn161.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn161.getText().toString());
                btn161.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button162:
                if(btn162.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn162.getText().toString());
                btn162.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button163:
                if(btn163.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn163.getText().toString());
                btn163.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button164:
                if(btn164.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn164.getText().toString());
                btn164.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button171:
                if(btn171.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn171.getText().toString());
                btn171.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button172:
                if(btn172.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn172.getText().toString());
                btn172.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button173:
                if(btn173.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn173.getText().toString());
                btn173.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button174:
                if(btn174.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn174.getText().toString());
                btn174.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            case R.id.button181:
                if(btn181.getText() == "")
                    p1Total += intScore;
                else
                    p1Total += intScore - Integer.parseInt(btn181.getText().toString());
                btn181.setText(score);
                btnTotP1.setText(String.valueOf(p1Total));
                break;
            case R.id.button182:
                if(btn182.getText() == "")
                    p2Total += intScore;
                else
                    p2Total += intScore - Integer.parseInt(btn182.getText().toString());
                btn182.setText(score);
                btnTotP2.setText(String.valueOf(p2Total));
                break;
            case R.id.button183:
                if(btn183.getText() == "")
                    p3Total += intScore;
                else
                    p3Total += intScore - Integer.parseInt(btn183.getText().toString());
                btn183.setText(score);
                btnTotP3.setText(String.valueOf(p3Total));
                break;
            case R.id.button184:
                if(btn184.getText() == "")
                    p4Total += intScore;
                else
                    p4Total += intScore - Integer.parseInt(btn184.getText().toString());
                btn184.setText(score);
                btnTotP4.setText(String.valueOf(p4Total));
                break;

            default:
                break;
        }
    }

    /** Called when the user taps the reset scorecard button */
    public void confirmResetCard(final View view) {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(this);
        alertDialog.setMessage("Are you sure you want to reset the scorecard?");

        alertDialog.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                resetCard();
            }
        });

        alertDialog.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                //do nothing
            }
        });

        alertDialog.create();
        alertDialog.show();
    }

    /** Called if user confirms yes to reset scorecard */
    public void resetCard() {
        btn11.setText("");
        btn12.setText("");
        btn13.setText("");
        btn14.setText("");

        btn21.setText("");
        btn22.setText("");
        btn23.setText("");
        btn24.setText("");

        btn31.setText("");
        btn32.setText("");
        btn33.setText("");
        btn34.setText("");

        btn41.setText("");
        btn42.setText("");
        btn43.setText("");
        btn44.setText("");

        btn51.setText("");
        btn52.setText("");
        btn53.setText("");
        btn54.setText("");

        btn61.setText("");
        btn62.setText("");
        btn63.setText("");
        btn64.setText("");

        btn71.setText("");
        btn72.setText("");
        btn73.setText("");
        btn74.setText("");

        btn81.setText("");
        btn82.setText("");
        btn83.setText("");
        btn84.setText("");

        btn91.setText("");
        btn92.setText("");
        btn93.setText("");
        btn94.setText("");

        btn101.setText("");
        btn102.setText("");
        btn103.setText("");
        btn104.setText("");

        btn111.setText("");
        btn112.setText("");
        btn113.setText("");
        btn114.setText("");

        btn121.setText("");
        btn122.setText("");
        btn123.setText("");
        btn124.setText("");

        btn131.setText("");
        btn132.setText("");
        btn133.setText("");
        btn134.setText("");

        btn141.setText("");
        btn142.setText("");
        btn143.setText("");
        btn144.setText("");

        btn151.setText("");
        btn152.setText("");
        btn153.setText("");
        btn154.setText("");

        btn161.setText("");
        btn162.setText("");
        btn163.setText("");
        btn164.setText("");

        btn171.setText("");
        btn172.setText("");
        btn173.setText("");
        btn174.setText("");

        btn181.setText("");
        btn182.setText("");
        btn183.setText("");
        btn184.setText("");

        btnTotP1.setText("");
        btnTotP2.setText("");
        btnTotP3.setText("");
        btnTotP4.setText("");
        p1Total = 0;
        p2Total = 0;
        p3Total = 0;
        p4Total = 0;
    }

    /** Called when the user taps the settings button */
    public void sendToSettings(View view) {
        Intent intent = new Intent(this, SettingsActivity.class);
        startActivity(intent);
    }

    /** Called when the user taps the back button */
    public void backToScreen2(View view) {
        Intent intent = new Intent(this, Screen2Activity.class);
        startActivity(intent);
    }

    public void addPlayer(View view) {
        Toast.makeText(ScorecardActivity.this, "Add Player Feature Coming Soon!", Toast.LENGTH_SHORT).show();
    }

    /** Called when the user leaves the scorecard */
    @Override
    protected void onStop() {
        super.onStop();
        SharedPreferences sharedPreferences = getSharedPreferences("cardInfo", 0);
        SharedPreferences.Editor e = sharedPreferences.edit();

        e.putString("btn11", btn11.getText().toString());
        e.putString("btn12", btn12.getText().toString());
        e.putString("btn13", btn13.getText().toString());
        e.putString("btn14", btn14.getText().toString());

        e.putString("btn21", btn21.getText().toString());
        e.putString("btn22", btn22.getText().toString());
        e.putString("btn23", btn23.getText().toString());
        e.putString("btn24", btn24.getText().toString());

        e.putString("btn31", btn31.getText().toString());
        e.putString("btn32", btn32.getText().toString());
        e.putString("btn33", btn33.getText().toString());
        e.putString("btn34", btn34.getText().toString());

        e.putString("btn41", btn41.getText().toString());
        e.putString("btn42", btn42.getText().toString());
        e.putString("btn43", btn43.getText().toString());
        e.putString("btn44", btn44.getText().toString());

        e.putString("btn51", btn51.getText().toString());
        e.putString("btn52", btn52.getText().toString());
        e.putString("btn53", btn53.getText().toString());
        e.putString("btn54", btn54.getText().toString());

        e.putString("btn61", btn61.getText().toString());
        e.putString("btn62", btn62.getText().toString());
        e.putString("btn63", btn63.getText().toString());
        e.putString("btn64", btn64.getText().toString());

        e.putString("btn71", btn71.getText().toString());
        e.putString("btn72", btn72.getText().toString());
        e.putString("btn73", btn73.getText().toString());
        e.putString("btn74", btn74.getText().toString());

        e.putString("btn81", btn81.getText().toString());
        e.putString("btn82", btn82.getText().toString());
        e.putString("btn83", btn83.getText().toString());
        e.putString("btn84", btn84.getText().toString());

        e.putString("btn91", btn91.getText().toString());
        e.putString("btn92", btn92.getText().toString());
        e.putString("btn93", btn93.getText().toString());
        e.putString("btn94", btn94.getText().toString());

        e.putString("btn101", btn101.getText().toString());
        e.putString("btn102", btn102.getText().toString());
        e.putString("btn103", btn103.getText().toString());
        e.putString("btn104", btn104.getText().toString());

        e.putString("btn111", btn111.getText().toString());
        e.putString("btn112", btn112.getText().toString());
        e.putString("btn113", btn113.getText().toString());
        e.putString("btn114", btn114.getText().toString());

        e.putString("btn121", btn121.getText().toString());
        e.putString("btn122", btn122.getText().toString());
        e.putString("btn123", btn123.getText().toString());
        e.putString("btn124", btn124.getText().toString());

        e.putString("btn131", btn131.getText().toString());
        e.putString("btn132", btn132.getText().toString());
        e.putString("btn133", btn133.getText().toString());
        e.putString("btn134", btn134.getText().toString());

        e.putString("btn141", btn141.getText().toString());
        e.putString("btn142", btn142.getText().toString());
        e.putString("btn143", btn143.getText().toString());
        e.putString("btn144", btn144.getText().toString());

        e.putString("btn151", btn151.getText().toString());
        e.putString("btn152", btn152.getText().toString());
        e.putString("btn153", btn153.getText().toString());
        e.putString("btn154", btn154.getText().toString());

        e.putString("btn161", btn161.getText().toString());
        e.putString("btn162", btn162.getText().toString());
        e.putString("btn163", btn163.getText().toString());
        e.putString("btn164", btn164.getText().toString());

        e.putString("btn171", btn171.getText().toString());
        e.putString("btn172", btn172.getText().toString());
        e.putString("btn173", btn173.getText().toString());
        e.putString("btn174", btn174.getText().toString());

        e.putString("btn181", btn181.getText().toString());
        e.putString("btn182", btn182.getText().toString());
        e.putString("btn183", btn183.getText().toString());
        e.putString("btn184", btn184.getText().toString());

        e.putString("btnTotP1", btnTotP1.getText().toString());
        e.putString("btnTotP2", btnTotP2.getText().toString());
        e.putString("btnTotP3", btnTotP3.getText().toString());
        e.putString("btnTotP4", btnTotP4.getText().toString());

        e.apply();
    }
}
